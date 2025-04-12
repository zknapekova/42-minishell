/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuknapek <zuknapek@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:18:57 by zuknapek          #+#    #+#             */
/*   Updated: 2025/04/12 19:09:34 by zuknapek         ###   ########.fr       */
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

void    	error_handler(char *str);
int 		init_env(char **env, t_data *data);
t_env_node	*new_node(t_data *data, char *key_value);
t_env_node	*last_node(t_data *data);
t_env_node	*search_env_list(t_data *data, char *var_name);
void		free_all(t_data *data);
int			get_first_occurr_index(char *str, char c);
int			replace_env_value(t_data *data, char *key_value);

#endif