/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 22:05:21 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/05/15 16:32:35 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"
#include "token.h"

int	check_first_token(t_token *tokens);
int	check_last_token(t_token *tokens);
int	check_chained_oper(t_token *tokens);

int	check_operator(t_token *tokens)
{
	t_token	*head;

	head = tokens;
	while (tokens->type != TOKEN_EOF)
	{
		if (tokens->type == TOKEN_LPAREN)
			head = tokens->next;
		if (head == tokens && !check_first_token(tokens))
			return (0);
		if (tokens->next->type == TOKEN_EOF \
			|| tokens->next->type == TOKEN_RPAREN)
		{
			if (!check_last_token(tokens))
				return (0);
		}
		if (tokens->type == TOKEN_AND || tokens->type == TOKEN_OR \
			|| tokens->type == TOKEN_PIPE)
		{
			if (!check_chained_oper(tokens))
				return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}

// operators should not be at the beginnig of a line
// or just after opening parenthesis

int	check_first_token(t_token *tokens)
{
	if (tokens->type == TOKEN_AND)
		return (ft_eprintf("minishell: \
syntax error near unexpected token `&&'\n"), 0);
	if (tokens->type == TOKEN_OR)
		return (ft_eprintf("minishell: \
syntax error near unexpected token `||'\n"), 0);
	if (tokens->type == TOKEN_PIPE)
		return (ft_eprintf("minishell: \
syntax error near unexpected token `|'\n"), 0);
	return (1);
}

// chcecks if there is an operator or a redirection at the end 
// of the command or before closing parenthesis

int	check_last_token(t_token *tokens)
{
	if (tokens->type == TOKEN_AND)
		return (ft_eprintf("minishell: \
syntax error: missing command after `&&'\n"), 0);
	if (tokens->type == TOKEN_OR)
		return (ft_eprintf("minishell: \
syntax error: missing command after `||'\n"), 0);
	if (tokens->type == TOKEN_PIPE)
		return (ft_eprintf("minishell: \
syntax error: missing command after `|'\n"), 0);
	if (tokens->type == TOKEN_REDIR_IN || tokens->type == TOKEN_REDIR_OUT \
		|| tokens->type == TOKEN_REDIR_APP)
	{
		if (tokens->next->type == TOKEN_EOF)
			return (ft_eprintf("minishell: \
syntax error near unexpected token `newline'\n"), 0);
		if (tokens->next->type == TOKEN_RPAREN)
			return (ft_eprintf("minishell: \
syntax error near unexpected token `)'\n"), 0);
	}
	return (1);
}

// checks if the operators are between commands
int	check_chained_oper(t_token *tokens)
{
	if (tokens->next->type == TOKEN_AND)
		return (ft_eprintf("minishell: \
syntax error near unexpected token `&&'\n"), 0);
	if (tokens->next->type == TOKEN_OR)
		return (ft_eprintf("minishell: \
syntax error near unexpected token `||'\n"), 0);
	if (tokens->next->type == TOKEN_PIPE)
		return (ft_eprintf("minishell: \
syntax error near unexpected token `|'\n"), 0);
	return (1);
}
