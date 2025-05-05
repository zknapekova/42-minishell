/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:35:54 by zuknapek          #+#    #+#             */
/*   Updated: 2025/05/05 19:10:40 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../include/token.h"
#include "../include/parser_utils.h"
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
	free_token_list(data->tokens);
	free(data);
}

// static void	free_redir(t_redir *redir)
// {
// 	t_redir	*temp;

// 	while (redir)
// 	{
// 		temp = redir->next;
// 		if (redir->filename)
// 			free (redir->filename);
// 		free (redir);
// 		redir = temp;
// 	}
// }

void	free_cmd(t_cmd_data *cmd)
{
	if (!cmd)
		return ;
	if (cmd->argv)
		free_args(cmd->argv);
	if (cmd->redirections)
		free_redir(cmd->redirections);
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
