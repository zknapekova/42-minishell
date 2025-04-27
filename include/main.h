/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuknapek <zuknapek@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:18:57 by zuknapek          #+#    #+#             */
/*   Updated: 2025/04/27 18:58:16 by zuknapek         ###   ########.fr       */
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
t_data	    *init_data();
t_env_node	*new_node(t_data *data, char *key_value);
t_env_node	*last_node(t_data *data);
t_env_node	*search_env_list(t_data *data, char *var_name);
int	        add_env(t_data *data, char *key_value);
void        update_node(t_env_node *node, char *key_value, int eq_ind);
void		free_all(t_data *data);
int	        get_first_ind(char *str, char c, int start);
int         get_first_occurr_non_alnum(char *str, int start);
int 		validate_env_var_name(char *key_value, int eq_ind);
int	        handle_new_env_value(t_data *data, char *key_value);

#endif