/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuknapek <zuknapek@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:18:57 by zuknapek          #+#    #+#             */
/*   Updated: 2025/05/09 20:44:11 by zuknapek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

typedef struct s_env_node
{
	char				*key_value;
	char				*key;
	char				*value;
	struct s_env_node	*next;
}	t_env_node;

//tato struktura moze byt pre vseobecne data, nie nevyhnutne iba pre env LL
typedef struct s_data
{
	t_env_node	*head;	//pointer to head of LL
}	t_data;

void		error_handler(char *str);
int			init_env(char **env, t_data *data);
t_data		*init_data(void);
t_env_node	*new_node(t_data *data, char *key_value);
t_env_node	*last_node(t_data *data);
t_env_node	*search_env_list(t_data *data, char *var_name);
void		free_all(t_data *data);
int			handle_new_env_value(t_data *data, char *key_value);
int			export(t_data *data, char *input);
int			pwd(void);
int			env_cmd(t_data *data);
int			unset(t_data *data, char **args);
int			echo(char *input, t_data *data, int n_param);

#endif