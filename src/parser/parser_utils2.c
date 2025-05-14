/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 23:09:07 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/05/13 18:53:42 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"

int	is_token_redir(t_token *tokens)
{
	if (tokens && ((tokens->type == TOKEN_REDIR_IN) \
	|| tokens->type == TOKEN_REDIR_OUT \
	||tokens->type == TOKEN_HEREDOC || tokens->type == TOKEN_REDIR_APP))
		return (1);
	else
		return (0);
}

int	is_token_redirin(t_token *tokens)
{
	if (tokens && tokens->type == TOKEN_REDIR_IN)
		return (1);
	else
		return (0);
}

int	is_token_redirout(t_token *tokens)
{
	if (tokens && tokens->type == TOKEN_REDIR_OUT)
		return (1);
	else
		return (0);
}

int	is_token_append(t_token *tokens)
{
	if (tokens && tokens->type == TOKEN_REDIR_APP)
		return (1);
	else
		return (0);
}

int	is_token_heredoc(t_token *tokens)
{
	if (tokens && tokens->type == TOKEN_HEREDOC)
		return (1);
	else
		return (0);
}
