/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:00:09 by zuknapek          #+#    #+#             */
/*   Updated: 2025/07/06 21:34:37 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_VARS_H
# define ENV_VARS_H
# include "main.h"

t_env_node	*new_node(t_data *data, char *key_value);
t_env_node	*last_node(t_data *data);
t_env_node	*search_env_list(t_data *data, char *var_name);
void		update_node(t_env_node *node, char *key_value, int eq_ind);
int			add_env(t_data *data, char *key_value);
int			delete_node(t_data *data, char *key);
int			lst_size(t_data *data);
char		*extend_var_name(int dollar_ind, int eq_ind, t_data *data, \
			char *key_value);
int			export_extend_env_value(t_data *data, char *key_value, \
			char *var_name, t_env_node *node_to_update);
int			validate_env_var_name(char *key_value, int eq_ind);
void		update_dollar_eq_ind(int *dollar_ind, int *eq_ind, \
			int dollar_start, char *key_value);
int			handle_new_node(t_env_node *node_to_update, t_data *data, \
			char *key_value);
char		*parse_env_value(t_env_node *node, char *key_value, \
			int dollar_ind, int eq_ind);
char		*get_key_value(char *var_to_extend, t_data *data, \
			char *key_value, char *var_name);
int			get_first_ind(char *str, char c, int start);
int			get_first_non_alnum(char *str, int start);
int			handle_new_env_value(t_data *data, char *key_value);
void		error_handler(char *str);
char		*add_new_line(char *str);
char		*echo_extend_env_value(t_data *data, char *key_value);
char		*extend_env_value(t_data *data, char *key_value);
char		*echo_get_key_value(char *var_to_extend, t_data *data, \
	char *key_value);
char		*replace_tilde(char *input, int ind);
char		*replace_special_parameter(char *str, t_data *data);
char		*replace_empty(char *str, t_data *data);
int			dir_check(char *path, char *cmd);
// no freeing the key_value
char		*extend_env_value_nf(t_data *data, char *key_value);
char		*get_key_value_nf(char *var_to_extend, t_data *data, \
	char *key_value);
int			ft_strcmp(const char *s1, const char *s2);
int			arr_size(char **arr);

#endif