/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 01:08:03 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/07/09 01:55:42 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "env_vars.h"
#include "main.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

char	**create_env_arr(t_data *data)
{
	int			size;
	char		**result;
	int			i;
	t_env_node	*temp;

	i = 0;
	temp = data->head;
	size = lst_size(data);
	result = (char **)malloc(sizeof(char *) * (size + 1));
	if (!result)
		return (error_handler("malloc error"), NULL);
	while (i < size && temp)
	{
		result[i++] = temp->key_value;
		temp = temp->next;
	}
	result[size] = NULL;
	return (result);
}

static void	find_closest_in_cmd(t_ast *node, int fd)
{
	if (node->type == NODE_COMMAND)
		node->cmd_data->fd_pipe_in = fd;
	else if (node->type == NODE_PIPE)
		find_closest_in_cmd(node->right, fd);
	else if (node->type == NODE_AND)
		find_closest_in_cmd(node->right, fd);
	else if (node->type == NODE_OR)
		find_closest_in_cmd(node->left, fd);
	else if (node->type == NODE_SUBSHELL)
		find_closest_in_cmd(node->left, fd);
}

static void	find_closest_out_cmd(t_ast *node, int fd)
{
	if (node->type == NODE_COMMAND)
		node->cmd_data->fd_pipe_out = fd;
	else if (node->type == NODE_AND)
		find_closest_out_cmd(node->right, fd);
	else if (node->type == NODE_OR)
		find_closest_out_cmd(node->left, fd);
	else if (node->type == NODE_SUBSHELL)
		find_closest_out_cmd(node->left, fd);
}

int	open_pipe(t_ast *node)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (error_handler(strerror(errno)), 0);
	find_closest_in_cmd(node->left, fd[1]);
	find_closest_out_cmd(node->right, fd[0]);
	return (1);
}

void	close_pipes(t_data *data, t_ast *node)
{
	if (!node)
		return ;
	if (node->type == NODE_COMMAND && node->cmd_data)
	{
		if (node->cmd_data->fd_pipe_in > 1)
		{
			close(node->cmd_data->fd_pipe_in);
		}
		if (node->cmd_data->fd_pipe_out > 1)
		{
			close(node->cmd_data->fd_pipe_out);
		}
	}
	close_pipes(data, node->left);
	close_pipes(data, node->right);
}
