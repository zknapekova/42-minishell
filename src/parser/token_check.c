/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 22:00:56 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/05/15 16:32:21 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"
#include "token.h"

static int	check_parentheses(t_token *tokens);
static int	check_redirect(t_token *tokens);

int	check_tokens(t_token *tokens)
{
	if (!check_parentheses(tokens) || !check_operator(tokens) \
	|| !check_redirect(tokens))
		return (0);
	return (1);
}

// check that every '(' has its corresponding ')'
static int	check_parentheses(t_token *tokens)
{
	int	paren_status;

	paren_status = 0;
	while (tokens)
	{
		if (tokens->type == TOKEN_LPAREN)
			paren_status++;
		if (tokens->type == TOKEN_RPAREN)
		{
			if (paren_status == 0)
			{
				error_handler("Syntax error: ')' before matching '('\n");
				return (0);
			}
			paren_status--;
		}
		tokens = tokens->next;
	}
	if (paren_status == 0)
		return (1);
	error_handler("Syntax error: unclosed '('\n");
	return (0);
}

// redirections should be followed by a word or a subshell, 
// in the case of HEREDOC, the << should be followed by 
// EOF sequence (word or a subshell?)
static int	check_redirect(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type >= TOKEN_REDIR_IN && tokens->type <= TOKEN_HEREDOC)
		{
			if (tokens->next->type == TOKEN_EOF)
				return (ft_eprintf("minishell: \
syntax error near unexpected token `newline'\n"), 0);
			if (tokens->next->type == TOKEN_RPAREN)
				return (ft_eprintf("minishell: \
syntax error near unexpected token `)'\n"), 0);
			if (tokens->next->type == TOKEN_AND)
				return (ft_eprintf("minishell: \
syntax error near unexpected token `&&'\n"), 0);
			if (tokens->next->type == TOKEN_OR)
				return (ft_eprintf("minishell: \
syntax error near unexpected token `||'\n"), 0);
			if (tokens->next->type == TOKEN_PIPE)
				return (ft_eprintf("minishell: \
syntax error near unexpected token `|'\n"), 0);
		}
		tokens = tokens->next;
	}
	return (1);
}
