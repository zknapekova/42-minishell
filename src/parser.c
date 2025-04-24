/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:28:09 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/04/23 23:54:31 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../libft/libft.h"
#include "../include/token.h"

int	check_tokens(t_token *tokens);
int	check_parentheses(t_token *tokens);


t_ast	*parser(t_token *tokens)
{
	// t_ast	*ast;

	if (!check_tokens(tokens))
		return (NULL);
	return (NULL);
}

int	check_tokens(t_token *tokens)
{
	if (!check_parentheses(tokens) || !check_)
		return (0);
	// while (tokens)
	// {
	// 	if (tokens->type == TOKEN_AND || tokens->type == TOKEN_OR)
	// 	{
	// 		if (tokens->next->type == TOKEN_EOF)
	// 			ft_eprintf("Syntax error: missing command after operator")
	// 	}
	// 	tokens = tokens->next;
	// }
	return (1);
}

int	check_parentheses(t_token *tokens)
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
