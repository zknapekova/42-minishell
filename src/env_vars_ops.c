/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_ops.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuknapek <zuknapek@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:47:56 by zuknapek          #+#    #+#             */
/*   Updated: 2025/04/13 19:32:52 by zuknapek         ###   ########.fr       */
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

char	*parse_env_value(t_env_node *node, char *key_value, int dollar_ind, int eq_ind)
{
	char		*new_key_value;
	char		*temp;
	char		*temp0;
	char		*substr;

	temp0 = ft_substr(key_value, eq_ind,  dollar_ind);
	if (!temp0)
		return(error_handler(strerror(errno)), NULL);
	temp = ft_strjoin(temp0, node->value);
	if (!temp)
		return (free(temp0), error_handler(strerror(errno)), NULL);
	free(temp0);
	substr = ft_substr(key_value, dollar_ind + ft_strlen(node->key) + 1, ft_strlen(key_value) - dollar_ind + ft_strlen(node->key) + 1);
	if (!substr)
		return (free(temp), error_handler(strerror(errno)), NULL);
	new_key_value = ft_strjoin(temp, substr);
	if (!new_key_value)
		return (free(temp), free(substr), error_handler(strerror(errno)), NULL);
	free(substr);
	free(temp);
	return (new_key_value);
}


#include <stdio.h>
int	extend_env_value(t_data *data, char *key_value, int dollar_ind)
{
	char		*var_name;
	char		*var_to_extend;
	t_env_node	*temp;
	t_env_node	*node;
	int			len;
	char		*new_key_value;
	char		**split_key_value;
	int			eq_ind;
	char		*message;

	
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

	eq_ind = get_first_occurr_index(key_value, '=');
	if (eq_ind == -1)
	{
		new_key_value = parse_env_value(temp, key_value, dollar_ind, 0);
		message = ft_strjoin("bash: export: '", new_key_value);
		return (error_handler("bash: export: "), 0);	
	}
	if (temp) //existuje premenna ktoru chceme dosadit?
		new_key_value = parse_env_value(temp, key_value, dollar_ind, eq_ind);
	else
	{
		new_key_value = ft_strjoin(var_name, "=");
		if (!new_key_value)
			return(error_handler(strerror(errno)), 0); 
	}
	node = search_env_list(data, var_name); // je to nova premenna alebo menime existujucu?
	if (node)
	{
		node->key_value = new_key_value;
		split_key_value = ft_split(new_key_value, '=');
		if (!split_key_value)
			return(error_handler(strerror(errno)), 0);
		node->key = split_key_value[0];
		node->value = split_key_value[1];
	}
	else
		add_env(data, new_key_value);
	printf("new_key_value: %s\n", node->key_value);
	printf("key: %s\n", node->key);
	printf("value: %s\n", node->value);
	return (1);
}

//This function should be called when prompt contains "export"
int	update_env_value(t_data *data, char *key_value)
{
	int		eq_ind;
	int		dollar_ind;
	
	dollar_ind = get_first_occurr_index(key_value, '$');
	if (dollar_ind != -1)
	{
		if (!extend_env_value(data, key_value, dollar_ind))
			return (0);
	}

	eq_ind = get_first_occurr_index(key_value, '=');
	if (eq_ind == -1)
		add_env(data, key_value);
	
	return (1);
}