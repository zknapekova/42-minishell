/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:54:24 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/04/18 23:41:43 by jgrigorj         ###   ########.fr       */
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
char 			*parse_quoted(const char *input, size_t *pos, char quote);
// char			*parse_word(const char *input, size_t *pos);

t_token	*lexer(const char *input)
{
	t_token			*tokens;
	size_t			pos;
	t_token_type	type;
	char			quote;
	char			*quoted;	

	ft_printf("***lexer called***\n");
	tokens = NULL;
	pos = 0;
	while (input[pos])
	{
		skipspace(input, &pos);
		if (!input[pos])
			break ;
		if (is_operator_char(input[pos]))
		{
			ft_printf("operator char found, pos %i\n", pos);
			type = match_operator(input, &pos);
			ft_printf("match_operator returned, pos %i\n", pos);
			if (type == TOKEN_INVALID)
			{
				ft_eprintf("Syntax error near unexpected character: '%c'\n", \
					input[pos]);
				free_token_list(tokens);
				return (NULL);
			}
			token_append(&tokens, new_token(type, NULL));
		}
		else if (input[pos] == '\'' || input[pos] == '"')
		{
			quote = input[pos];
			quoted = parse_quoted(input, &pos, quote);
			if (!quoted)
			{
				free_token_list(tokens);
				return (NULL);
			}
			token_append(&tokens, new_token(TOKEN_WORD, quoted));
			free (quoted);
		}
		// else parse_word
	}
	token_append(&tokens, new_token(TOKEN_EOF, NULL));
	return (tokens);
}

static void	skipspace(const char *input, size_t *pos)
{
	ft_printf("skipspace called, pos %i\n", *pos);
	while (input[*pos] == ' ')
		(*pos)++;
}

static int	is_operator_char(char c)
{
	ft_printf("is_operator_char called\n");
	if (c == '|' || c == '&' || c == '<' || c == '>' || c == '(' || c == ')')
		return (1);
	else
		return (0);
}

t_token_type	match_operator(const char *input, size_t *pos)
{
	ft_printf("match_operator called, pos %i\n", *pos);
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

// parse quoted string
char *parse_quoted(const char *input, size_t *pos, char quote)
{
	ft_printf("parse_quoted called\n");
	size_t	start;
	size_t	len;
	char	*word;

	start = ++(*pos);
	while (input[*pos] && input[*pos] != quote)
		(*pos)++;
	if (input[*pos] != quote)
		return (ft_eprintf("Unclosed quote: %c\n", quote), NULL);
	len = *pos - start;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (error_handler("Error allocating quoted string"), NULL);
	ft_strlcpy(word, &input[start], len + 1);
	(*pos)++;
	return (word);
}

// // parse unquoted word
// char	*parse_word(const char *input, size_t *pos)
// {
// 	size_t	start;
	
// 	start = *pos;
// 	while (input[*pos] && input[*pos] != ' ' && !is_operator_char(input[*pos]) && input[*pos] != '\'' && input[*pos] != '"')
// 		(*pos)++;
	
// }