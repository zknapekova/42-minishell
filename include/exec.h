/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:15:04 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/05/24 20:31:03 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "main.h"

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

#endif