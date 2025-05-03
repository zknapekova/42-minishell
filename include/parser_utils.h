#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

#include "../include/main.h"

int	is_token_pipe(t_token *tokens);
int	is_token_and(t_token *tokens);
int	is_token_or(t_token *tokens);
int	is_token_lparen(t_token *tokens);
int	is_token_rparen(t_token *tokens);
int	is_token_word(t_token *tokens);
int	is_token_redir(t_token *tokens);
int	is_token_redirin(t_token *tokens);
int	is_token_redirout(t_token *tokens);
int	is_token_append(t_token *tokens);
int	is_token_heredoc(t_token *tokens);
int	is_token_pipe(t_token *tokens);
void	advance_token(t_token **tokens);
void	append_arg(t_arg **head, const char *value, t_quote_type qtype, t_word_join wjoin);
void	free_args(t_arg *head);

#endif