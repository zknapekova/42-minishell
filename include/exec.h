/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:15:04 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/07 20:00:52 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "main.h"

typedef struct s_file
{
	char			*name;
	// unsigned char	d_type;
	struct s_file	*next;
}	t_file;

char	**get_argv(t_data *data, t_arg *args);
char	*get_arg_str(t_data *data, t_arg **args);
void	print_ast_argv(t_data *data, t_ast *node, int depth);
int		get_list_len(t_arg *args);
void	free_argv(char **argv);
char	*get_redir_target_str(t_data *data, t_redir_target *target);
void	setup_heredoc(char *target);
char	*get_exec_path(const char *cmd, t_data *data);

int		echo_cmd(char **input, t_data *data);
int		cd(char **input, t_data *data);
int		execute_built_cmds(char **argv, t_data *data);
int		check_built_ins(char *cmd);
int		ft_redirect(int input_fd, int output_fd);
int		handle_redir_files(t_redir *redir, t_data *data);
char	**create_env_arr(t_data *data);
char	*escape_wildcard(char *str);

char	*get_path_from_env(const char *cmd, t_data *data);
char	*handle_path(char *path, int free_path, int folder, int existence_check);
int		get_fd_file(char *path, t_redir_type type);
char	*get_cmd_path(char *cmd, t_data *data);
int		arr_size(char **arr);
void	free_array(char **array);
int		open_pipe(t_ast *node);
int		process_cmds_redirs(t_data *data, t_ast *node, int pid);
void	find_cmds(t_data *data, t_ast *node);
void	handle_cmds(t_data *data, t_ast *node);
void	close_pipes(t_data *data, t_ast *node);

// globbing
char	**globe_argv(char **argv);
char	**get_globbed_argv(char **new_argv, char *argv, t_bool *match_found);
char	**get_unglobbed_argv(char **new_argv, char *argv, t_bool match_found);
char	*globe_redir_target(char *target);
char	*get_globbed_target(char *target, int *match_count);
int		is_match(char *str, t_file *file_list);
char	*handle_ambiguous_error(char *target, t_file *head);
t_file	*append_file(t_file *head, const char *name);
void	free_file_list(t_file *head);
t_file	*get_cwd_file_list(void);
int 	match_star_pattern(char *pattern, char *str);
int		is_in_cwd(char *str);
char	**append_str_to_array(char **arr, char *str);
char	*rm_escape_char(char *str);
int		is_hidden_file(char *str);
int		longer_strlen(char *str1, char *str2);
t_file	*sorted_insert(t_file *head, t_file *new_node);
t_file	*sort_file_list(t_file *head);



#endif