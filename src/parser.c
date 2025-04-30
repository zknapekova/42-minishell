/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:28:09 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/04/28 23:14:00 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../libft/libft.h"
#include "../include/token.h"
#include "../include/parser_utils.h"

t_ast	*parser(t_token *tokens)
{
	t_ast	*ast;

	if (!check_tokens(tokens))
		return (NULL);
	ast = parse_and_or(tokens);
	return (NULL);
}

t_ast	*new_ast_node(t_node_type type)
{
	t_ast	*new_node;

	new_node = malloc(sizeof(t_ast));
	if (!new_node)
		return (error_handler("Failed to allocate new ast node\n"), NULL);
	new_node->type = type;
	new_node->cmd_data = malloc(sizeof(t_cmd_data));
	if (!new_node->cmd_data)
	{
		free(new_node);
		return (error_handler("Failed to allocate cmd_data\n"), NULL);
	}
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

t_ast	*parse_and_or(t_token *tokens)
{
	
}