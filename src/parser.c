/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:28:09 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/04/30 20:53:48 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../libft/libft.h"
#include "../include/token.h"
#include "../include/parser_utils.h"

t_ast	*new_ast_node(t_node_type type);

t_ast	*parse_or(t_token **tokens);
t_ast	*parse_and(t_token **tokens);
t_ast	*parse_pipeline(t_token **tokens);
t_ast	*parse_cmd_or_subshell(t_token **tokens);
t_ast	*parse_subshell(t_token **tokens);
t_ast	*parse_cmd(t_token **tokens);

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
			return (error_handler("Failed to allocate new ast NODE_OR\n"), NULL);
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
			return (error_handler("Failed to allocate new ast NODE_AND\n"), NULL);
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
	while (is_token_and(*tokens))
	{	
		advance_token(tokens);
		right = parse_cmd_or_subshell(tokens);
		pipe_node = new_ast_node(NODE_PIPE);
		if (!pipe_node)
			return (error_handler("Failed to allocate new ast NODE_PIPE\n"), NULL);
		pipe_node->left = left;
		pipe_node->right = right;
		left = pipe_node;
	}
	return (left);
}

t_ast	*parse_cmd_or_subshell(t_token **tokens)
{
	if (is_token_lparen(*tokens))
		return (parse_subshell(tokens));
	else
		return (parse_cmd(tokens));
}

t_ast	*parse_subshell(t_token **tokens)
{
	t_ast	*subtree;
	t_ast	*subshell_node;
	
	if (!is_token_lparen(*tokens))
		return (error_handler("Expected '('\n"), NULL);
	advance_token(tokens);
	subtree = parse_or(tokens);
	if (!subtree)
		return (error_handler("Failed parsing subshell/n"), NULL);
	if (!is_token_rparen(*tokens))
	{
		free_ast(subtree);
		return (error_handler("Expected ')'\n"), NULL);
	}
	advance_token(tokens);
	subshell_node = new_ast_node(NODE_SUBSHELL);
	if (!subshell_node)
	{
		free_ast(subtree);
		return (error_handler("Failed creating subshell node/n"), NULL);
	}
	subshell_node->left = subtree;
	subshell_node->right = NULL;
	return (subshell_node);
}

t_ast	*parse_cmd(t_token **tokens)
{
	
}