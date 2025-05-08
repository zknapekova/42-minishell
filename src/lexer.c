/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:54:24 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/05/07 22:45:57 by jgrigorj         ###   ########.fr       */
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
static int			handle_word(const char *input, \
	size_t *pos, t_token **tokens);
static int			handle_operator(const char *input, \
	size_t *pos, t_token **tokens);
static t_word_join	word_join_or_split(char next_char);

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
	token_append(&tokens, new_token(TOKEN_EOF, NULL, QUOTE_NONE, W_SPLIT));
	return (tokens);
}

static int	handle_operator(const char *input, size_t *pos, t_token **tokens)
{
	t_token_type	type;
	t_token			*tok;

	type = match_operator(input, pos);
	if (type == TOKEN_INVALID)
	{
		ft_eprintf("Syntax error near unexpected character: '%c'\n", \
			input[*pos]);
		return (0);
	}
	tok = new_token(type, NULL, QUOTE_NONE, W_SPLIT);
	if (!tok)
		return (error_handler("Token creation failed\n"), 0);
	token_append(tokens, tok);
	return (1);
}

static int	handle_word(const char *input, size_t *pos, t_token **tokens)
{
	char			*word;
	t_quote_type	quote_type;
	t_word_join		word_join;
	t_token			*tok;

	if (input[*pos] == '\'' || input[*pos] == '"')
	{
		if (input[*pos] == '\'')
			quote_type = QUOTE_SINGLE;
		if (input[*pos] == '"')
			quote_type = QUOTE_DOUBLE;
		word = parse_quoted(input, pos, input[*pos]);
	}
	else
	{
		word = parse_word(input, pos);
		quote_type = QUOTE_NONE;
	}
	if (!word)
		return (0);
	word_join = word_join_or_split(input[*pos]);
	tok = new_token(TOKEN_WORD, word, quote_type, word_join);
	free(word);
	if (!tok)
		return (error_handler("Token creation failed\n"), 0);
	token_append(tokens, tok);
	return (1);
}

static t_word_join	word_join_or_split(char next_char)
{
	t_word_join	word_join;

	if (next_char == '\'' || next_char == '"' \
		|| ft_isalnum(next_char) || next_char == '$')
		word_join = W_JOIN;
	else
		word_join = W_SPLIT;
	return (word_join);
}
