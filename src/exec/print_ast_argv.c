/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast_argv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:05:38 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/07/09 00:10:33 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"
#include "env_vars.h"
#include "exec.h"
#include "parser_utils.h" // for print_indent()
#include <stdlib.h> //for NULL  

void	print_ast_argv(t_data *data, t_ast *node, int depth)
{
	char	**argv;
	int		i;
	char	*redir_target;
	t_redir	*redir;
	// char	*path;

	i = 0;
	if (!node)
		return ;
	print_indent(depth);
	ft_printf("**node type: %s\n", node_type_to_str(node->type));
	if ((node->type == NODE_COMMAND || node->type == NODE_SUBSHELL) \
	&& node->cmd_data)
	{
		if (node->cmd_data->args)
		{
			argv = get_argv(data, node->cmd_data->args);
			if (!argv)
				return ;
			print_indent(depth + 1);
			ft_printf("**argv: ");
			while (argv[i])
				ft_printf("%s, ", argv[i++]);
			// ft_printf("path: %s", path);
			ft_printf("\n");
			free_argv(argv);
			// free (path);
		}
		if (node->cmd_data->redirs)
		{
			print_indent(depth + 1);
			ft_printf("**redirs:\n");
			redir = node->cmd_data->redirs;
			while (redir && redir->target)
			{
				redir_target = get_redir_target_str(data, redir->target);
				if (!redir_target)
					return ;
				print_indent(depth + 2);
				ft_printf("typ: %s, target: %s\n", \
					redir_type_to_str(redir->type), redir_target);
				free (redir_target);
				redir = redir->next;
			}
		}
	}
	print_ast_argv(data, node->left, depth + 1);
	print_ast_argv(data, node->right, depth + 1);
}
