/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:00:36 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/28 22:40:50 by jgrigorj         ###   ########.fr       */
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
#include <sys/wait.h>

char	*get_redir_target_str(t_data *data, t_redir_target *target)
{
	char			*target_str;
	char			*tmp_str;
	t_redir_target	*head;

	target_str = NULL;
	if (!target || !target->value)
		return (NULL);
	head = target;
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
	if (!target_str[0])
		return(free (target_str), ft_eprintf("minishell: %s: ambiguous redirect\n", head->value), NULL);
	target_str = globe_redir_target(target_str);
	return (target_str);
}

int	ft_redirect(t_ast *node)
{
	int	input_fd;
	int	output_fd;

	input_fd = -1;
	output_fd = -1;
	if (node->cmd_data->fd_file_in != -1)
		input_fd = node->cmd_data->fd_file_in;
	else if (node->cmd_data->fd_pipe_out != -1)
		input_fd = node->cmd_data->fd_pipe_out;
	if (node->cmd_data->fd_file_out != -1)
		output_fd = node->cmd_data->fd_file_out;
	else if (node->cmd_data->fd_pipe_in != -1)
		output_fd = node->cmd_data->fd_pipe_in;
	if (input_fd > 1)
	{
//		ft_printf("fd %d redirected to stdin\n", input_fd);
		if (dup2(input_fd, STDIN_FILENO) < 0)
			return (error_handler(strerror(errno)), 0);
		close(input_fd);
	}
	if (output_fd > 1)
	{
//		ft_printf("fd %d redirected to stdout\n", output_fd);
		if (dup2(output_fd, STDOUT_FILENO) < 0)
			return (error_handler(strerror(errno)), 0);
		close(output_fd);
	}
	return (1);
}

// This function fills fd_file for each redirection, except for REDIR_HEREDOC and REDIR_INVALID
int	handle_redir_files(t_redir *redir, t_data *data, t_ast *node)
{
	char	*redir_file_path;
	char	*updated_path;
	int		status;

	while (redir && redir->target)
	{
		if (redir->type != REDIR_HEREDOC && redir->type != REDIR_INVALID)
		{
			redir_file_path = get_redir_target_str(data, redir->target);
			if (!redir_file_path)
				return (EXIT_FAILURE);
			updated_path = handle_path(redir_file_path, 1, 0, 0);
			if (!updated_path)
				return (EXIT_FAILURE);
			if (redir->type == REDIR_INPUT)
			{
				node->cmd_data->fd_file_in = get_fd_file(updated_path, redir->type);
				if (node->cmd_data->fd_file_in == -1)
					return (free (updated_path), EXIT_FAILURE);
//				ft_printf("file was opened with fd %d\n", node->cmd_data->fd_file_in);
			}
			if (redir->type == REDIR_OUTPUT || redir->type == REDIR_APPEND)
			{
				node->cmd_data->fd_file_out = get_fd_file(updated_path, redir->type);
				if (node->cmd_data->fd_file_out == -1)
					return (free (updated_path), EXIT_FAILURE);
			}
			free (updated_path);
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



