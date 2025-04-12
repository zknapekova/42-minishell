/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_ops.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuknapek <zuknapek@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:47:56 by zuknapek          #+#    #+#             */
/*   Updated: 2025/04/12 19:21:18 by zuknapek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../libft/libft.h"
#include "stdlib.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>

t_env_node	*search_env_list(t_data *data, char *var_name)
{
	t_env_node	*temp;
	size_t		len;
	
	if (data->head && var_name)
	{
		temp = data->head;
		len = ft_strlen(var_name);
		while (temp)
		{
			if (ft_strncmp(temp->key, var_name, len) == 0)
				return (temp);
			temp = temp->next;
		}
	}
	return (NULL);
}

int	add_env(t_data *data, char *key_value)
{
	t_env_node	*node;
	t_env_node	*lastnode;
	
	if (data->head && key_value)
	{
		node = new_node(data, key_value);
		if (!node)
			return (0);
		lastnode = last_node(data);
		lastnode->next = node;
	}
	return (1);
}

int init_env(char **env, t_data *data)
{
    t_env_node *node;
	t_env_node *last;

	node = new_node(data, *env);
	if (!node)
		return (0);
	while (*env)
	{
        node = new_node(data, *env);
		if (!node)
			return(0);
        last = last_node(data);
        last->next = node;
        env++;
	}
    return (1);
}


#include <stdio.h>
void	extend_env_value(t_data *data, char *key_value, int dollar_ind)
{
	char		*var_name;
	char		*var_to_extend;
	t_env_node	*temp;
	int			len;
	//char		*new_key_value;
	
	var_name = ft_substr(key_value, 0, get_first_occurr_index(key_value, '='));
	temp = data->head;
	while (temp)
	{
		len = ft_strlen(temp->key);
		var_to_extend = ft_substr(key_value, dollar_ind + 1, len);
		if (ft_strncmp(var_to_extend, temp->key, len) == 0)
			break;
		temp = temp->next;
	}
	printf("temp_key_value %s temp key: %s temp_value: %s\n", temp->key_value, temp->key, temp->value);
	//new_key_value = ft_strjoin(temp->value, )
}

//TODO: implement change of env value in two ways: export PATH="/new/path" but also export PATH=$PATH:/new/directory/path 
int	replace_env_value(t_data *data, char *key_value)
{
	int		eq_ind;
	int		dollar_ind;
	//char	*var_name;
	
	dollar_ind = get_first_occurr_index(key_value, '$');
	if (dollar_ind != -1)
	{
		extend_env_value(data, key_value, dollar_ind);
	}
	
	eq_ind = get_first_occurr_index(key_value, '=');
	if (eq_ind == -1)
		add_env(data, key_value);
	
	return (1);
}