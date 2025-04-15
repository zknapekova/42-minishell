/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:18:57 by zuknapek          #+#    #+#             */
/*   Updated: 2025/04/13 20:21:51 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

typedef struct s_env_node
{
    char                *key_value;
	char				*key;
	char				*value;
    struct s_env_node   *next;
}   t_env_node;

//tato struktura moze byt pre vseobecne data, nie nevyhnutne iba pre env LL
typedef struct s_data
{
	t_env_node	*head;	//pointer to head of LL
}	t_data;

// parsing and AST

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
	TOKEN_REDIR_APP,
	TOKEN_HEREDOC,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_EOF
} t_token_type;

typedef struct s_token
{
    t_token_type type;
    char *value;
} t_token;

typedef enum e_node_type
{
    NODE_COMMAND,
    NODE_PIPE,
    NODE_AND,
    NODE_OR,
    NODE_SUBSHELL
} t_node_type;

// **argv is the standard argument vector passed to execve()
// Example: ["ls", "-la", "/home", NULL]
typedef struct s_cmd_data {
    char **argv;
    // Add redirection data later
} t_cmd_data;

// t_cmd_data cmd is used only if type is NODE_COMMAND
typedef struct s_ast
{
    t_node_type type;
    struct s_ast *left;
    struct s_ast *right;
    t_cmd_data cmd;
} t_ast;


void    	error_handler(char *str);
int 		init_env(char **env, t_data *data);
t_env_node	*new_node(t_data *data, char *key_value);
t_env_node	*last_node(t_data *data);
t_env_node	*search_env_list(t_data *data, char *var_name);
void		free_all(t_data *data);
int			get_first_occurr_index(char *str, char c);
int			replace_env_value(t_data *data, char *key_value);

// signal
void	sig_init(void);

#endif