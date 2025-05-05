/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:18:57 by zuknapek          #+#    #+#             */
/*   Updated: 2025/05/05 19:10:53 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

typedef enum e_bool
{
	true = 1,
	false = 0
}	t_bool;

typedef struct s_env_node
{
	char				*key_value;
	char				*key;
	char				*value;
	struct s_env_node	*next;
}	t_env_node;

// *** parsing and AST ***

// TOKEN_REDIR_IN,    // <
// TOKEN_REDIR_OUT,   // >
// TOKEN_REDIR_APP,   // >>
// TOKEN_HEREDOC,     // <<
// TOKEN_LPAREN,      // (
// TOKEN_RPAREN,      // )
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APP,
	TOKEN_HEREDOC,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_EOF,
	TOKEN_INVALID
}	t_token_type;

typedef enum e_quote_type
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}	t_quote_type;

typedef enum e_word_join
{
	W_SPLIT,
	W_JOIN
}	t_word_join;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	t_quote_type	quote_type;
	t_word_join		word_join;
	struct s_token	*next;
}	t_token;

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_SUBSHELL
}	t_node_type;

typedef enum e_redir_type
{
	REDIR_INPUT,
	REDIR_OUTPUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	REDIR_DUP
}	t_redir_type;

// the char *target is the filename or heredoc limiter or fd for >& syntax
// the t_bool is_fd_target is for the >& syntax
typedef struct s_redir
{
	t_redir_type	type;
	int				fd;
	char			*target;
	t_bool			is_fd_target;
	struct s_redir	*next;
}	t_redir;

typedef struct s_arg
{
	char	*value;
	t_quote_type	quote_type;
	t_word_join		word_join;
	struct s_arg	*next;
} t_arg;

// t_arg	*argv is a linked list of argument data (to be expanded later)
// t_arg *argv will be used to generate the **argv
// **argv is the standard argument vector passed to execve()
// Example: ["ls", "-la", "/home", NULL]
typedef struct s_cmd_data
{
	t_arg	*argv;
	t_redir *redirections; // Linked list of I/O redirections
}	t_cmd_data;

// t_cmd_data cmd is used only if type is NODE_COMMAND
typedef struct s_ast
{
	t_node_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
	t_cmd_data		*cmd_data;
}	t_ast;

// *** main data structure ***
//tato struktura moze byt pre vseobecne data, nie nevyhnutne iba pre env LL
typedef struct s_data
{
	t_env_node	*head;	//pointer to head of LL
	t_token		*tokens;
	t_ast		*ast;
}	t_data;


void		error_handler(char *str);
int			init_env(char **env, t_data *data);
t_env_node	*new_node(t_data *data, char *key_value);
t_env_node	*last_node(t_data *data);
t_env_node	*search_env_list(t_data *data, char *var_name);
void		free_all(t_data *data);
int			get_first_occurr_index(char *str, char c);
int			replace_env_value(t_data *data, char *key_value);

// *** signal ***
void		sig_init(void);

// lexer
t_token		*lexer(const char *input);

// parser
t_ast		*parser(t_token **tokens);
void		free_ast(t_ast *node);
void	free_cmd(t_cmd_data *cmd);


#endif