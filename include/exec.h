/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:15:04 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/05/24 18:32:15 by jgrigorj         ###   ########.fr       */
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
void	free_array(char **array);

#endif