/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuknapek <zuknapek@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:17:55 by zuknapek          #+#    #+#             */
/*   Updated: 2025/05/03 16:56:40 by zuknapek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/env_vars.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

void	update_dollar_eq_ind(int *dollar_ind, int *eq_ind, int dollar_start, \
			char *key_value)
{
	*dollar_ind = get_first_ind(key_value, '$', dollar_start);
	*eq_ind = get_first_ind(key_value, '=', 0);
}

int	handle_new_node(t_env_node *node_to_update, t_data *data, char *key_value)
{
	if (!node_to_update)
	{
		if (!add_env(data, key_value))
			return (error_handler(strerror(errno)), 0);
	}
	else
		update_node(node_to_update, key_value, \
			get_first_ind(key_value, '=', 0));
	return (1);
}

t_env_node	*search_env_list(t_data *data, char *key)
{
	t_env_node	*temp;
	size_t		len;

	if (data->head && key)
	{
		temp = data->head;
		len = ft_strlen(key);
		while (temp)
		{
			if (ft_strncmp(temp->key, key, len) == 0 && \
					len == ft_strlen(temp->key))
				return (temp);
			temp = temp->next;
		}
	}
	return (NULL);
}

char	*parse_env_value(t_env_node *node, char *key_value, int dollar_ind, \
	int eq_ind)
{
	char	*new_value;
	char	*temp;
	char	*temp0;
	char	*substr;

	temp0 = ft_substr(key_value, eq_ind + 1, dollar_ind - eq_ind - 1);
	if (!temp0)
		return (error_handler(strerror(errno)), NULL);
	temp = ft_strjoin(temp0, node->value);
	if (!temp)
		return (free(temp0), error_handler(strerror(errno)), NULL);
	free(temp0);
	substr = ft_substr(key_value, dollar_ind + ft_strlen(node->key) + 1, \
			ft_strlen(key_value) - dollar_ind + ft_strlen(node->key) + 1);
	if (!substr)
		return (free(temp), error_handler(strerror(errno)), NULL);
	new_value = ft_strjoin(temp, substr);
	if (!new_value)
		return (free(temp), free(substr), error_handler(strerror(errno)), NULL);
	free(substr);
	free(temp);
	return (new_value);
}

char	*get_key_value(char *var_to_extend, t_data *data, char *key_value, \
	char *var_name)
{
	char	*temp_key_value;
	char	*new_key_value;
	char	*new_value;
	int		dollar_ind;

	dollar_ind = get_first_ind(key_value, '$', 0);
	if (!search_env_list(data, var_to_extend))
	{
		temp_key_value = ft_substr(key_value, 0, dollar_ind);
		new_value = ft_substr(key_value, get_first_non_alnum(key_value, \
			dollar_ind + 1), ft_strlen(key_value) - \
			get_first_non_alnum(key_value, dollar_ind + 1));
	}
	else
	{
		temp_key_value = ft_strjoin(var_name, "=");
		new_value = parse_env_value(search_env_list(data, var_to_extend), \
		key_value, dollar_ind, get_first_ind(key_value, '=', 0));
	}
	if (!temp_key_value || !new_value)
		return (error_handler(strerror(errno)), NULL);
	new_key_value = ft_strjoin(temp_key_value, new_value);
	if (get_first_ind(key_value, '$', 0) == -1)
		free(key_value);
	return (free(temp_key_value), free(new_value), new_key_value);
}
