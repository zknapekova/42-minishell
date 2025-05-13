/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:31:41 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/05/13 18:54:39 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include <stdlib.h> // for malloc
#include "../libft/libft.h" //for ft_printf
#include "../include/token.h"
#include "../include/parser_utils.h"

int	is_token_word(t_token *tokens)
{
	if (tokens && tokens->type == TOKEN_WORD)
		return (1);
	else
		return (0);
}

// moves to the next node in the token list
// reference to the list is passed to change the list
// (we move the start of the list to the next token)
void	advance_token(t_token **tokens)
{
	if (*tokens)
		*tokens = (*tokens)->next;
}

t_ast	*new_ast_node(t_node_type type)
{
	t_ast	*new_node;

	new_node = malloc(sizeof(t_ast));
	if (!new_node)
		return (ft_eprintf("Failed to allocate new ast %s node\n", \
			node_type_to_str(type)), NULL);
	new_node->type = type;
	new_node->cmd_data = NULL;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}
