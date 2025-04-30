/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 22:51:30 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/04/28 23:08:39 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

int	is_token_pipe(t_token *tokens)
{
	if (tokens && tokens->type == TOKEN_PIPE)
		return (1);
	else
		return (0);
}

int	is_token_and(t_token *tokens)
{
	if (tokens && tokens->type == TOKEN_AND)
		return (1);
	else
		return (0);
}

int	is_token_of(t_token *tokens)
{
	if (tokens && tokens->type == TOKEN_OR)
		return (1);
	else
		return (0);
}

int	is_token_lparen(t_token *tokens)
{
	if (tokens && tokens->type == TOKEN_LPAREN)
		return (1);
	else
		return (0);
}

int	is_token_rparen(t_token *tokens)
{
	if (tokens && tokens->type == TOKEN_RPAREN)
		return (1);
	else
		return (0);
}
