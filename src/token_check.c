/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 22:00:56 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/04/26 19:51:25 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../libft/libft.h"
#include "../include/token.h"

int	check_parentheses(t_token *tokens);

int	check_tokens(t_token *tokens)
{
	if (!check_parentheses(tokens) || !check_operator(tokens))
		return (0);
// check redirect
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
