// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   parser.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/04/23 17:28:09 by jgrigorj          #+#    #+#             */
// /*   Updated: 2025/05/03 19:05:37 by jgrigorj         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

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
t_redir	*parse_redirection(t_token **tokens);

t_ast	*parser(t_token **tokens)
{
	// t_ast	*ast;

	if (!(*tokens) || !check_tokens(*tokens))
		return (NULL);
	// ast = parse_or(tokens);
	// return (ast);
	return (parse_or(tokens));
	// return (NULL);
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
	t_cmd_data	*cmd;
	t_redir		*redir;
	t_ast		*cmd_node;
	
	cmd = malloc(sizeof(t_cmd_data));
	if (!cmd)
		return (error_handler("Failed to allocate cmd inside parse_cmd\n"), NULL);
	cmd->argv = NULL;
	cmd->redirections = NULL;
	while (*tokens && (is_token_word(*tokens) || is_token_redir(*tokens)))
	{
		if (is_token_redir(*tokens))
		{
			redir = parse_redirection(tokens);
			if (!redir)
				return (error_handler("Failed to parse redirection\n"), NULL);
			append_redir(&cmd->redirections, redir);
		}
		else if (is_token_word(*tokens))
		{
			append_arg(&cmd->argv, (*tokens)->value, (*tokens)->quote_type, (*tokens)->word_join);
			advance_token(tokens);
		}
		// handle command substitution $(cmd)
		// handle subshell (...)
		// free_redir(redir);
	}
	cmd_node = new_ast_node(NODE_COMMAND);
	if (!cmd_node)
		return (free_cmd(cmd), error_handler("Failed to allocate cmd_node\n"), NULL);
	cmd_node->type = NODE_COMMAND;
	cmd_node->left = NULL; // change if subshell is found -> cmd_node->left = parse_subshell
	cmd_node->right = NULL;
	cmd_node->cmd_data = cmd;
	return (cmd_node);
}

t_redir	*parse_redirection(t_token **tokens)
{
	t_redir	*redir;

	if (!is_token_redir(*tokens) || !(*tokens)->next)
		return (error_handler("Invalid token in parse_redirection()\n"), NULL);
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (error_handler("Failed to allocate redir\n"), NULL);
	if (is_token_redirin(*tokens))
		redir->type = REDIR_INPUT;
	else if (is_token_redirout(*tokens))
		redir->type = REDIR_OUTPUT;
	else if (is_token_append(*tokens))
		redir->type = REDIR_APPEND;
	else if (is_token_heredoc(*tokens))
		redir->type = REDIR_HEREDOC;
	else 
		return (free (redir), error_handler("Unknown redirection type"), NULL);
	advance_token(tokens);
	if (!(*tokens) || (*tokens)->type != TOKEN_WORD)
		return (free (redir), error_handler("Expected filename or delimiter\n"), NULL);
	redir->target = ft_strdup((*tokens)->value);
	if (!redir->target)
		return (free(redir), error_handler("Failed to copy filename in parse_redirection\n"), NULL);
	redir->fd = -1; // We can further expand it to handle things like 2> error.log
	redir->next = NULL;

	return (redir);
}