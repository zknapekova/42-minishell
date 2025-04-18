/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:54:24 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/04/17 17:44:12 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../include/token.h"
#include "../libft/libft.h" // for ft_strncpm
// #include <aio.h> // defines size_t type
#include <stdlib.h>  // here for the NULL and size_t definitions

// the lexer separates the command line into individual tokens
// returns a linked list of tokens (*tokens) with elements of the t_token type

static void		skipspace(const char *input, size_t *pos);
static int		is_operator_char(char c);
t_token_type	match_operator(const char *input, size_t *pos);

t_token	*lexer(const char *input)
{
	t_token			*tokens;
	size_t			pos;
	t_token_type	type;

	tokens = NULL;
	pos = 0;
	while (input[pos])
	{
		skipspace(input, &pos);
		if (!input[pos])
			break ;
		if (is_operator_char(input[pos]))
		{
			type = match_operator(input, &pos);
			if (type == TOKEN_INVALID)
			{
				ft_eprintf(stderr, \
					"Syntax error near unexpected character: '%c'\n", \
					input[pos]);
				free_token_list(tokens);
				return (NULL);
			}
			token_append(&tokens, new_token(type, NULL));
		}
		
	}
	
	return (tokens);
}

static void	skipspace(const char *input, size_t *pos)
{
	while (input[*pos] == ' ')
		(*pos)++;
}

static int	is_operator_char(char c)
{
	if (c == '|' || c == '&' || c == '<' || c == '>' || c == '(' || c == ')')
		return (1);
	else
		return (0);
}

t_token_type	match_operator(const char *input, size_t *pos)
{
	if (ft_strncmp(&input[*pos], "&&", 2) == 0)
		return (*pos += 2, TOKEN_AND);
	if (ft_strncmp(&input[*pos], "||", 2) == 0)
		return (*pos += 2, TOKEN_OR);
	if (ft_strncmp(&input[*pos], "<<", 2) == 0)
		return (*pos += 2, TOKEN_HEREDOC);
	if (ft_strncmp(&input[*pos], ">>", 2) == 0)
		return (*pos += 2, TOKEN_REDIR_APP);
	if (input[*pos] == '|')
		return (*pos += 1, TOKEN_PIPE);
	if (input[*pos] == '<')
		return (*pos += 1, TOKEN_REDIR_IN);
	if (input[*pos] == '>')
		return (*pos += 1, TOKEN_REDIR_OUT);
	if (input[*pos] == '(')
		return (*pos += 1, TOKEN_LPAREN);
	if (input[*pos] == ')')
		return (*pos += 1, TOKEN_RPAREN);
	return (*pos -= 1, TOKEN_INVALID);
}