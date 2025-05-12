/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:32:07 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/05/12 18:40:00 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "main.h"
# include <stdlib.h>  // here for the NULL and size_t definitions

t_token			*new_token(t_token_type type, const char *value, \
	t_quote_type quote, t_word_join word_join);
void			token_append(t_token **head, t_token *new_token);
void			free_token_list(t_token **head);
void			print_tokens(t_token *tokens);
void			skipspace(const char *input, size_t *pos);
int				is_oper_ch(char c);
t_token_type	match_operator(const char *input, size_t *pos);
char			*parse_quoted(const char *input, size_t *pos, char quote);
char			*parse_word(const char *input, size_t *pos);
int				check_tokens(t_token *tokens);
int				check_operator(t_token *tokens);


#endif