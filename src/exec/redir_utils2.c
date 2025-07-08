/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 01:07:45 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/07/09 17:30:15 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_vars.h"
#include "exec.h"
#include "libft.h"	
#include "main.h"
#include <errno.h>
#include <stdlib.h> //for NULL
#include <string.h>
#include <sys/wait.h>

void	get_input_output_fd(int *input_fd, int *output_fd, t_ast *node)
{
	*input_fd = -1;
	*output_fd = -1;
	if (node->cmd_data->fd_file_in != -1)
		*input_fd = node->cmd_data->fd_file_in;
	else if (node->cmd_data->fd_pipe_out != -1)
		*input_fd = node->cmd_data->fd_pipe_out;
	if (node->cmd_data->fd_file_out != -1)
		*output_fd = node->cmd_data->fd_file_out;
	else if (node->cmd_data->fd_pipe_in != -1)
		*output_fd = node->cmd_data->fd_pipe_in;
}

int	input_output_redirect(t_data *data, t_redir *redir, t_ast *node)
{
	char	*redir_file_path;
	char	*updated_path;

	redir_file_path = get_redir_target_str(data, redir->target);
	if (!redir_file_path)
		return (EXIT_FAILURE);
	updated_path = handle_path(redir_file_path, 1, 0, 0);
	if (!updated_path)
		return (EXIT_FAILURE);
	if (redir->type == REDIR_INPUT)
	{
		node->cmd_data->fd_file_in = get_fd_file(updated_path,
				redir->type);
		if (node->cmd_data->fd_file_in == -1)
			return (free(updated_path), EXIT_FAILURE);
	}
	if (redir->type == REDIR_OUTPUT || redir->type == REDIR_APPEND)
	{
		node->cmd_data->fd_file_out = get_fd_file(updated_path,
				redir->type);
		if (node->cmd_data->fd_file_out == -1)
			return (free(updated_path), EXIT_FAILURE);
	}
	return (free(updated_path), EXIT_SUCCESS);
}

void	replace_target_value(t_redir_target *target, char *str)
{
	free(target->value);
	target->value = str;
}

void	handle_tilde_in_target(t_redir_target *target)
{
	int		tilde_ind;
	char	*tilde_replaced;

	tilde_ind = get_first_ind(target->value, '~', 0);
	if (tilde_ind != -1 && target->quote_type == QUOTE_NONE)
	{
		tilde_replaced = replace_tilde(target->value, tilde_ind);
		if (tilde_replaced)
			replace_target_value(target, tilde_replaced);
	}
}

char	*handle_env_expansion(t_data *data, t_redir_target *target)
{
	char	*tmp_str;

	tmp_str = NULL;
	if (get_first_ind(target->value, '$', 0) != -1
		&& target->quote_type != QUOTE_SINGLE)
		tmp_str = extend_env_value_nf(data, target->value);
	else
		tmp_str = ft_strdup(target->value);
	return (tmp_str);
}
