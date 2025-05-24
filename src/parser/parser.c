/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:32:45 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/05/18 21:55:11 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"
#include "token.h"
#include "parser_utils.h"

t_ast	*parser(t_token **tokens)
{
	if (!(*tokens) || !check_tokens(*tokens))
		return (NULL);
	return (parse_or(tokens));
}

t_ast	*parse_or(t_token **tokens)
{
	t_ast	*left;
	t_ast	*right;
	t_ast	*or_node;

	left = parse_and(tokens);
	while (is_token_or(*tokens))
	{
		advance_token(tokens);
		right = parse_and(tokens);
		or_node = new_ast_node(NODE_OR);
		if (!or_node)
			return (NULL);
		or_node->left = left;
		or_node->right = right;
		left = or_node;
	}
	return (left);
}

t_ast	*parse_and(t_token **tokens)
{
	t_ast	*left;
	t_ast	*right;
	t_ast	*and_node;

	left = parse_pipeline(tokens);
	while (is_token_and(*tokens))
	{
		advance_token(tokens);
		right = parse_pipeline(tokens);
		and_node = new_ast_node(NODE_AND);
		if (!and_node)
			return (NULL);
		and_node->left = left;
		and_node->right = right;
		left = and_node;
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
