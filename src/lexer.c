/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:54:24 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/04/21 18:54:03 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../include/token.h"
#include "../libft/libft.h" // for ft_strncpm
// #include <aio.h> // defines size_t type
#include <stdlib.h>  // here for the NULL and size_t definitions
#include <signal.h> // for the SIG type macro

// the lexer separates the command line into individual tokens
// returns a linked list of tokens (*tokens) with elements of the t_token type
extern sig_atomic_t	g_sigstate;
int	handle_word(const char *input, size_t *pos, t_token **tokens);
int	handle_operator(const char *input, size_t *pos, t_token **tokens);

t_token	*lexer(const char *input)
{
	t_token			*tokens;
	size_t			pos;

	tokens = NULL;
	pos = 0;
	while (input[pos] && g_sigstate != SIGQUIT && g_sigstate != SIGINT)
	{
		skipspace(input, &pos);
		if (!input[pos])
			break ;
		if (is_oper_ch(input[pos]))
		{
			if (!handle_operator(input, &pos, &tokens))
				return (free_token_list(tokens), NULL);
		}
		else
		{
			if (!handle_word(input, &pos, &tokens))
				return (free_token_list(tokens), NULL);
		}
	}
	token_append(&tokens, new_token(TOKEN_EOF, NULL));
	return (tokens);
}

int	handle_operator(const char *input, size_t *pos, t_token **tokens)
{
	t_token_type	type;

	type = match_operator(input, pos);
	if (type == TOKEN_INVALID)
	{
		ft_eprintf("Syntax error near unexpected character: '%c'\n", \
			input[*pos]);
		return (0);
	}
	token_append(tokens, new_token(type, NULL));
	return (1);
}

int	handle_word(const char *input, size_t *pos, t_token **tokens)
{
	char	*word;

	if (input[*pos] == '\'' || input[*pos] == '"')
		word = parse_quoted(input, pos, input[*pos]);
	else
		word = parse_word(input, pos);
	if (!word)
		return (0);
	token_append(tokens, new_token(TOKEN_WORD, word));
	free(word);
	return (1);
}
