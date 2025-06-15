/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:00:36 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/04 19:07:21 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"
#include "env_vars.h"
#include "exec.h"
#include "parser_utils.h" // for print_indent()
#include <stdlib.h> //for NULL
#include <errno.h>
#include <string.h>

char	*get_redir_target_str(t_data *data, t_redir_target *target)
{
	char			*target_str;
	char			*tmp_str;

	target_str = NULL;
	if (!target)
		return (NULL);
	while (target && target->value)
	{
		if (get_first_ind(target->value, '$', 0) != -1 \
		&& target->quote_type != QUOTE_SINGLE)
			tmp_str = extend_env_value_nf(data, target->value);
		else
			tmp_str = ft_strdup(target->value);
		if (!tmp_str)
			return (free (target_str), \
			error_handler("Error getting target_str"), NULL);
		target_str = ft_strjoin_ed(target_str, tmp_str, ft_strlen(tmp_str));
		free (tmp_str);
		if (!target_str)
			return (error_handler("Error getting target_str"), NULL);
		target = target->next;
	}
	target_str = globe_redir_target(target_str);
	return (target_str);
}

int	ft_redirect(int input_fd, int output_fd)
{
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

// This function fills fd_file for each redirection, except for REDIR_HEREDOC and REDIR_INVALID
int	handle_redir_files(t_redir *redir, t_data *data)
{
	char	*redir_file_path;
	char	*updated_path;

	while (redir && redir->target)
	{
		if (redir->type != REDIR_HEREDOC && redir->type != REDIR_INVALID)
		{
			redir_file_path = get_redir_target_str(data, redir->target);
			if (!redir_file_path)
				return (0);
			updated_path = handle_path(redir_file_path, 1, 0, 0);
			if (!updated_path)
				return (0);
			redir->target->fd_file = get_fd_file(updated_path, redir->type);
			if (redir->target->fd_file == -1)
				return (free (updated_path), 0);
			free (updated_path);
			if (redir->type == REDIR_INPUT)
				ft_redirect(redir->target->fd_file, -1);
			if (redir->type == REDIR_OUTPUT || redir->type == REDIR_APPEND)
				ft_redirect(-1, redir->target->fd_file);
		}
		redir = redir->next;
	}
	return (1);
}



