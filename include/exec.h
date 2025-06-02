/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:15:04 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/02 19:33:01 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "main.h"

typedef struct s_file
{
	char			*name;
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

char	*get_path_from_env(const char *cmd, t_data *data);
void	free_array(char **array);

// globbing
t_file	*append_file(t_file *head, const char *name);
void	free_file_list(t_file *head);
t_file	*get_cwd_file_list(void);
int 	match_star_pattern(char *pattern, char *str);
int		is_in_cwd(char *str);
char	**append_str_to_array(char **arr, char *str);

#endif