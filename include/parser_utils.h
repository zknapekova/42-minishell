#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

#include "../include/main.h"

int	is_token_pipe(t_token *tokens);
int	is_token_and(t_token *tokens);
int	is_token_of(t_token *tokens);
int	is_token_lparen(t_token *tokens);
int	is_token_rparen(t_token *tokens);
int	is_token_word(t_token *tokens);
int	is_token_redirin(t_token *tokens);
int	is_token_redirout(t_token *tokens);
int	is_token_append(t_token *tokens);
int	is_token_heredoc(t_token *tokens);
int	is_token_pipe(t_token *tokens);

#endif