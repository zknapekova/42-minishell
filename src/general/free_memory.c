/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:35:54 by zuknapek          #+#    #+#             */
/*   Updated: 2025/05/19 19:06:25 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "token.h"
#include "parser_utils.h"
#include <stdlib.h>
#include <stdio.h>

static void	free_ll(t_data *data)
{
	t_env_node	*temp;

	if (data->head)
	{
		while (data->head)
		{
			temp = data->head->next;
			free(data->head->key_value);
			free(data->head->key);
			free(data->head->value);
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
	if (cmd->args)
		free_args(cmd->args);
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


void	free_redir(t_redir *head)
{
	t_redir			*next;
	t_redir_target	*next_target;

	while (head)
	{
		next = head->next;
		while (head->target)
		{
			next_target = head->target->next;
			free (head->target->value);
			free (head->target);
			head->target = next_target;
		}
		free (head);
		head = next;
	}
}
