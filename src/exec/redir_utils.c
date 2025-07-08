/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:00:36 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/07/09 00:08:08 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_vars.h"
#include "exec.h"
#include "libft.h"
#include "main.h"
#include "parser_utils.h" // for print_indent()
#include <errno.h>
#include <stdlib.h> //for NULL
#include <string.h>
#include <sys/wait.h>

static void	replace_target_value(t_redir_target *target, char *str);


char	*process_target_str(t_data *data, t_redir_target *target)
{
	int		tilde_ind;
	char	*tilde_replaced;
	char	*tmp_str;
	char	*target_str;

	target_str = NULL;
	tilde_ind = get_first_ind(target->value, '~', 0);
	if (tilde_ind != -1 && target->quote_type != QUOTE_SINGLE)
	{
		tilde_replaced = replace_tilde(target->value, tilde_ind);
		if (tilde_replaced)
			replace_target_value(target, tilde_replaced);
	}
	if (get_first_ind(target->value, '$', 0) != -1
		&& target->quote_type != QUOTE_SINGLE)
		tmp_str = extend_env_value_nf(data, target->value);
	else
		tmp_str = ft_strdup(target->value);
	if (!tmp_str)
		return (free(target_str), error_handler("Error getting target_str"),
			NULL);
	target_str = ft_strjoin_ed(target_str, tmp_str, ft_strlen(tmp_str));
	return (free(tmp_str), target_str);
}


char	*get_redir_target_str(t_data *data, t_redir_target *target)
{
	char			*target_str;
	t_redir_target	*head;

	target_str = NULL;
	if (!target || !target->value)
		return (NULL);
	head = target;
	while (target && target->value)
	{
		target_str = process_target_str(data, target);
		if (!target_str)
			return (error_handler("Error getting target_str"), NULL);
		target = target->next;
	}
	if (!target_str[0])
		return (free(target_str), ft_eprintf("minishell: \
%s: ambiguous redirect\n", head->value), NULL);
	target_str = globe_redir_target(target_str);
	return (target_str);
}

int	ft_redirect(t_ast *node)
{
	int	input_fd;
	int	output_fd;

	get_input_output_fd(&input_fd, &output_fd, node);
	if (input_fd > 1)
	{
		if (dup2(input_fd, STDIN_FILENO) < 0)
			return (error_handler(strerror(errno)), 0);
		close(input_fd);
	}
	if (output_fd > 1)
	{
		if (dup2(output_fd, STDOUT_FILENO) < 0)
			return (error_handler(strerror(errno)), 0);
		close(output_fd);
	}
	return (1);
}


int	handle_redir_files(t_redir *redir, t_data *data, t_ast *node)
{
	int		status;

	while (redir && redir->target)
	{
		if (redir->type != REDIR_HEREDOC && redir->type \
		!= REDIR_INVALID)
		{
			if (input_output_redirect(data, redir, node) == 1)
				return (1);
		}
		else if (redir->type == REDIR_HEREDOC)
		{
			status = execute_heredoc(redir, data, node);
			if (status != 0)
				return (status);
		}
		redir = redir->next;
	}
	return (EXIT_SUCCESS);
}

static void	replace_target_value(t_redir_target *target, char *str)
{
	free(target->value);
	target->value = str;
}
