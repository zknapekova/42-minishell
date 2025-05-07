/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:00:55 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/05/06 17:36:54 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../libft/libft.h" // for ft_printf

void		print_indent(int depth);
const char	*node_type_to_str(t_node_type type);
const char	*redir_type_to_str(t_redir_type type);

void	print_argv(t_arg *argv, int depth)
{
	if (!argv)
		return ;
	print_indent(depth);
	ft_printf("**argv: ");
	while (argv)
	{
		if (argv->value)
			ft_printf("%s, ", argv->value);
		argv = argv->next;
	}
	ft_printf("\n");
}

void	print_redir(t_redir *redir, int depth)
{
	if (!redir)
		return ;
	print_indent(depth);
	ft_printf("**redir:\n");
	while (redir)
	{
		print_indent(depth + 1);
		if (redir->target)
			ft_printf("type: %s, target: %s\n", redir_type_to_str(redir->type), redir->target);
		redir = redir->next;
	}
}

void	print_cmd_data(t_cmd_data *cmd, int depth)
{
	if (!cmd)
		return ;
	print_argv(cmd->argv, depth);
	if (cmd->redirections)
		print_redir(cmd->redirections, depth);
}

void	print_ast(t_ast *node, int depth)
{
	if (!node)
		return ;
	print_indent(depth);
	ft_printf("**node type: %s\n", node_type_to_str(node->type));
	if (node->type == NODE_COMMAND && node->cmd_data)
		print_cmd_data(node->cmd_data, depth + 1);
	ft_printf("\n");
	print_ast(node->left, depth + 1);
	print_ast(node->right, depth + 1);
}

void	print_indent(int depth)
{
	while (depth-- > 0)
		ft_printf("  ");
}

const char	*node_type_to_str(t_node_type type)
{
	if (type == NODE_COMMAND)
		return ("COMMAND");
	else if (type == NODE_PIPE)
		return ("PIPE");
	else if (type == NODE_AND)
		return ("AND");
	else if (type == NODE_OR)
		return ("OR");
	else if (type == NODE_SUBSHELL)
		return ("SUBSHELL");
	return ("UNKNOWN");
}

const char	*redir_type_to_str(t_redir_type type)
{
	if (type == REDIR_INPUT)
		return ("IN");
	else if (type == REDIR_OUTPUT)
		return ("OUT");
	else if (type == REDIR_APPEND)
		return ("APPEND");
	else if (type == REDIR_HEREDOC)
		return ("HEREDOC");
	return ("UNKNOWN");
}