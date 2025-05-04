/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuknapek <zuknapek@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:00:09 by zuknapek          #+#    #+#             */
/*   Updated: 2025/05/04 18:28:34 by zuknapek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_VARS_H
# define ENV_VARS_H

typedef struct s_env_node
{
	char				*key_value;
	char				*key;
	char				*value;
	struct s_env_node	*next;
}	t_env_node;

typedef struct s_data
{
	t_env_node	*head;
}	t_data;

t_env_node	*new_node(t_data *data, char *key_value);
t_env_node	*last_node(t_data *data);
t_env_node	*search_env_list(t_data *data, char *var_name);
void		update_node(t_env_node *node, char *key_value, int eq_ind);
int			add_env(t_data *data, char *key_value);
int			delete_node(t_data *data, char *key);
char		*extend_var_name(int dollar_ind, int eq_ind, t_data *data, \
			char *key_value);
int			extend_env_value(t_data *data, char *key_value, \
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
int			validate_env_var_name(char *key_value, int eq_ind);
int			handle_new_env_value(t_data *data, char *key_value);
void		error_handler(char *str);

#endif