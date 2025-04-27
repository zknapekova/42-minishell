/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:28:09 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/04/27 22:01:55 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../libft/libft.h"
#include "../include/token.h"

// t_ast	*new_ast_node(void);

t_ast	*parser(t_token *tokens)
{
	// t_ast	*ast;

	if (!check_tokens(tokens))
		return (NULL);
	// ast = new_ast_node();
	return (NULL);
}

// t_ast	*new_ast_node(t_node_type *type, t_cmd_data *data)
// {
// 	t_ast	*new_node;

// 	new_node = malloc(sizeof(t_ast));
// 	if (!new_node)
// 		return (error_handler("Failed to allocate new ast node\n"), NULL);
// 	new_node->
// }