/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 18:31:14 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/04/21 19:02:49 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>  // here for the NULL and size_t definitions
#include "../include/main.h"
#include "../include/token.h"
// for ft_strncpm, ft_strlcpy, ft_isspace, ft_eprintf
#include "../libft/libft.h" 

void	skipspace(const char *input, size_t *pos)
{
	while (ft_isspace(input[*pos]))
		(*pos)++;
}

int	is_oper_ch(char c)
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
	return (TOKEN_INVALID);
}

// parse quoted string
char	*parse_quoted(const char *input, size_t *pos, char quote)
{
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

// parse unquoted word
char	*parse_word(const char *input, size_t *p)
{
	size_t	start;
	char	*word;
	char	*quoted;

	start = *p;
	word = NULL;
	while (input[*p] && !ft_isspace(input[*p]) && !is_oper_ch(input[*p]))
	{
		while (input[*p] && !ft_isspace(input[*p]) && !is_oper_ch(input[*p]) \
		&& input[*p] != '\'' && input[*p] != '"')
			(*p)++;
		word = ft_strjoin_ed(word, &input[start], *p - start);
		if (!word)
			return (error_handler("Error lexing word token"), NULL);
		if (input[*p] == '\'' || input[*p] == '"')
		{
			quoted = parse_quoted(input, p, input[*p]);
			if (!quoted)
				return (free (word), \
				error_handler("Error lexing word token"), NULL);
			word = ft_strjoin_ed(word, quoted, ft_strlen(quoted));
			free (quoted);
		}
	}
	return (word);
}
