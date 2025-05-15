/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:35:54 by zuknapek          #+#    #+#             */
/*   Updated: 2025/05/15 16:26:55 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "token.h"
#include "parser_utils.h"
#include <stdlib.h>

static void	free_ll(t_data *data)
{
	t_env_node	*temp;

	if (data->head)
	{
		while (data->head)
		{
			temp = data->head->next;
			free(data->head);
			data->head = temp;
		}
	}
}

void	free_all(t_data *data)
{
	free_ll(data);
	free_token_list(&(data->tokens));
	free(data);
}

void	free_cmd(t_cmd_data *cmd)
{
	if (!cmd)
		return ;
	if (cmd->argv)
		free_args(cmd->argv);
	if (cmd->redirs)
		free_redir(cmd->redirs);
	free(cmd);
}

void	free_ast(t_ast *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	free_cmd(node->cmd_data);
	free(node);
}
