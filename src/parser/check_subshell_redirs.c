/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_subshell_redirs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 15:54:01 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/27 16:04:49 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"
#include "parser_utils.h"

int	check_subshell_redirs(t_ast *node)
{
	int	result;

	result = 0;
	if (!node)
		return (0);
	if (node->type == NODE_SUBSHELL && node->cmd_data && node->cmd_data->redirs)
	{
		ft_eprintf("syntax error: redirections are not supported in subshells\n");
		return (1);
	}
	result += check_subshell_redirs(node->left);
	result += check_subshell_redirs(node->right);
	return (result);
}
void	set_heredoc_flag(t_ast *node)
{
	t_redir	*redir;

	if (!node)
		return ;
	if (node->type == NODE_COMMAND && node->cmd_data)
	{
		redir = node->cmd_data->redirs;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
				node->cmd_data->has_heredoc = true;
			redir = redir->next;
		}
	}
	set_heredoc_flag(node->left);
	set_heredoc_flag(node->right);
}
