/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:39:33 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/05/19 19:06:25 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"
#include "token.h"
#include "parser_utils.h"

t_ast	*parse_cmd_or_subshell(t_token **tokens)
{
	t_redir	*leading_redir;

	leading_redir = NULL;
	if (is_token_redir(*tokens))
	{
		leading_redir = collect_redirs(tokens);
		if (!leading_redir)
			return (error_handler("Error in parsing leading redirections"), \
			NULL);
	}
	if (is_token_lparen(*tokens))
		return (parse_subshell(tokens, leading_redir));
	else
		return (parse_cmd(tokens, leading_redir));
}

t_ast	*parse_subshell(t_token **tokens, t_redir *leading_redir)
{
	t_ast		*subtree;
	t_ast		*subshell_node;

	advance_token(tokens);
	subtree = parse_or(tokens);
	if (!subtree)
		return (error_handler("Failed parsing subshell/n"), NULL);
	if (!is_token_rparen(*tokens))
		return (free_ast(subtree), error_handler("Expected ')'\n"), NULL);
	advance_token(tokens);
	subshell_node = new_ast_node(NODE_SUBSHELL);
	if (!subshell_node)
		return (free_ast(subtree), NULL);
	subshell_node->left = subtree;
	subshell_node->cmd_data = init_cmd_data(leading_redir);
	if (!subshell_node->cmd_data)
		return (free(subshell_node), free_ast(subtree), \
		free_redir(leading_redir), NULL);
	append_redir(&subshell_node->cmd_data->redirs, collect_redirs(tokens));
	return (subshell_node);
}

t_ast	*parse_cmd(t_token **tokens, t_redir *leading_redir)
{
	t_ast		*cmd_node;

	cmd_node = new_ast_node(NODE_COMMAND);
	if (!cmd_node)
		return (NULL);
	cmd_node->cmd_data = init_cmd_data(leading_redir);
	if (!cmd_node->cmd_data)
		return (free_ast(cmd_node), NULL);
	while (*tokens && (is_token_word(*tokens) || is_token_redir(*tokens)))
	{
		append_redir(&cmd_node->cmd_data->redirs, collect_redirs(tokens));
		if (is_token_word(*tokens))
		{
			append_arg(&cmd_node->cmd_data->args, (*tokens)->value, \
			(*tokens)->quote_type, (*tokens)->word_join);
			advance_token(tokens);
		}
	}
	if (is_token_lparen(*tokens))
	{
		return (free_ast(cmd_node), error_handler("Subshells are not \
supported as command arguments\n"), NULL);
	}
	return (cmd_node);
}
