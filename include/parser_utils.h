/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 21:33:08 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/05/21 16:43:31 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

# include "../include/main.h"

t_ast			*new_ast_node(t_node_type type);
t_ast			*parse_or(t_token **tokens);
t_ast			*parse_and(t_token **tokens);
t_ast			*parse_pipeline(t_token **tokens);
t_ast			*parse_cmd_or_subshell(t_token **tokens);
t_ast			*parse_subshell(t_token **tokens, t_redir *leading_redir);
t_ast			*parse_cmd(t_token **tokens, t_redir *leading_redir);
int				is_token_pipe(t_token *tokens);
int				is_token_and(t_token *tokens);
int				is_token_or(t_token *tokens);
int				is_token_lparen(t_token *tokens);
int				is_token_rparen(t_token *tokens);
int				is_token_word(t_token *tokens);
int				is_token_redir(t_token *tokens);
int				is_token_redirin(t_token *tokens);
int				is_token_redirout(t_token *tokens);
int				is_token_append(t_token *tokens);
int				is_token_heredoc(t_token *tokens);
int				is_token_pipe(t_token *tokens);
void			advance_token(t_token **tokens);
void			append_arg(t_arg **head, const char *value, \
	t_quote_type qtype, t_word_join wjoin);
void			free_args(t_arg *head);
t_cmd_data		*init_cmd_data(t_redir *leading_redir);
void			append_redir(t_redir **redir_list, t_redir *new_redir);
void			free_redir(t_redir *head);
void			print_ast(t_ast *node, int depth);
void			print_redir(t_redir *redir, int depth);
void			print_indent(int depth);
const char		*node_type_to_str(t_node_type type);
const char		*redir_type_to_str(t_redir_type type);
const char		*quote_type_to_str(t_quote_type type);
t_redir			*parse_redirection(t_token **tokens);
t_redir			*collect_redirs(t_token **tokens);
t_redir_type	get_redir_type(t_token **tokens);

#endif