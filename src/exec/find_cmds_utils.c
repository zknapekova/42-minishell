/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmds_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:07:03 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/07/09 19:07:04 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_vars.h"
#include "exec.h"
#include "libft.h"
#include "main.h"
#include "parser_utils.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

void	exec_node_or(t_data *data, t_ast *node, int *status, int *status_stat)
{
	find_cmds(data, node->left, status_stat);
	update_last_status(data, *status_stat);
	wait_all_cmds(data, data->ast, status_stat);
	*status = *status_stat;
	if (*status_stat == EXIT_SUCCESS || *status_stat == 130)
		return ;
	find_cmds(data, node->right, status_stat);
	update_last_status(data, *status_stat);
	*status = *status_stat;
}

void	exec_node_and(t_data *data, t_ast *node, int *status, int *status_stat)
{
	find_cmds(data, node->left, status_stat);
	update_last_status(data, *status_stat);
	wait_all_cmds(data, data->ast, status_stat);
	*status = *status_stat;
	if (*status_stat != EXIT_SUCCESS)
		return ;
	find_cmds(data, node->right, status_stat);
	update_last_status(data, *status_stat);
	wait_all_cmds(data, data->ast, status_stat);
	*status = *status_stat;
}

void	exec_node_cmd(t_data *data, t_ast *node, int *status, int *status_stat)
{
	*status_stat = process_cmds_redirs(data, node);
	node->cmd_data->status = *status_stat;
	if (node->cmd_data->fd_pipe_in > 1)
		close(node->cmd_data->fd_pipe_in);
	if (node->cmd_data->fd_pipe_out > 1)
		close(node->cmd_data->fd_pipe_out);
	if (node->cmd_data->fd_file_in > 1)
		close(node->cmd_data->fd_file_in);
	if (node->cmd_data->fd_file_out > 1)
		close(node->cmd_data->fd_file_out);
	update_last_status(data, *status_stat);
	*status = *status_stat;
}

void	handle_logical(t_data *data, t_ast *node, int *status, int *status_stat)
{
	if (node->type == NODE_OR)
	{
		exec_node_or(data, node, status, status_stat);
		return ;
	}
	if (node->type == NODE_AND)
	{
		exec_node_and(data, node, status, status_stat);
		return ;
	}
}
