/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:32:45 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/07/06 21:20:47 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"
#include "parser_utils.h"
#include "token.h"

t_ast	*parser(t_token **tokens)
{
	if (!(*tokens) || !check_tokens(*tokens))
		return (NULL);
	return (parse_logical(tokens));
}

t_ast	*parse_logical(t_token **tokens)
{
	t_ast	*left;
	t_ast	*right;
	t_ast	*node;
	t_token	*operator_token;

	left = parse_pipeline(tokens);
	while (is_token_and(*tokens) || is_token_or(*tokens))
	{
		operator_token = *tokens;
		advance_token(tokens);
		right = parse_pipeline(tokens);
		if (is_token_and(operator_token))
			node = new_ast_node(NODE_AND);
		else
			node = new_ast_node(NODE_OR);
		if (!node)
			return (NULL);
		node->left = left;
		node->right = right;
		left = node;
	}
	return (left);
}

t_ast	*parse_pipeline(t_token **tokens)
{
	t_ast	*left;
	t_ast	*right;
	t_ast	*pipe_node;

	left = parse_cmd_or_subshell(tokens);
	while (is_token_pipe(*tokens))
	{
		advance_token(tokens);
		right = parse_cmd_or_subshell(tokens);
		pipe_node = new_ast_node(NODE_PIPE);
		if (!pipe_node)
			return (NULL);
		pipe_node->left = left;
		pipe_node->right = right;
		left = pipe_node;
	}
	return (left);
}
