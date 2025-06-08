/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:33:35 by zuknapek          #+#    #+#             */
/*   Updated: 2025/06/08 16:14:41 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/env_vars.h"
#include "../libft/libft.h"
#include <errno.h>
#include <string.h>

//will be used for unset cmd
// unset var1 var2 ->multiple variables can be specified
int	delete_node(t_data *data, char *key)
{
	t_env_node	*prev;
	t_env_node	*temp;

	if (data->head && key)
	{
		temp = data->head;
		prev = data->head;
		while (temp)
		{
			if (ft_strncmp(temp->key, key, ft_strlen(key)) == 0 && \
				ft_strlen(key) == ft_strlen(temp->key))
			{
				prev->next = temp->next;
				free(temp->key_value);
				free(temp->value);
				free(temp->key);
				free(temp);
				return (1);
			}
			prev = temp;
			temp = temp->next;
		}
	}
	return (0);
}

int	update_env_list(char *key_value, int eq_ind, t_data *data, int dollar_ind)
{
	char		*var_name;
	t_env_node	*node_to_update;

	var_name = ft_substr(key_value, 0, eq_ind);
	if (!var_name)
		return (error_handler(strerror(errno)), 0);
	node_to_update = search_env_list(data, var_name);
	if (dollar_ind == -1)
	{
		if (!handle_new_node(node_to_update, data, key_value))
			return (0);
	}
	else
	{
		if (!extend_env_value(data, key_value, var_name, node_to_update))
			return (free(var_name), 0);
	}
	return (free(var_name), 1);
}

//This function should be called when prompt contains "export"
int	handle_new_env_value(t_data *data, char *key_value)
{
	int		eq_ind;
	int		dollar_ind;

	update_dollar_eq_ind(&dollar_ind, &eq_ind, 0, key_value);
	if (eq_ind == -1 || (eq_ind != -1 && !validate_env_var_name(key_value, \
			eq_ind)))
		return (error_handler("minishell: export: '{key_value}': not a \
			valid identifier"), 0);
	if (dollar_ind != -1 && dollar_ind < eq_ind)
	{
		key_value = extend_var_name(dollar_ind, eq_ind, data, key_value);
		if (!key_value)
			return (0);
		update_dollar_eq_ind(&dollar_ind, &eq_ind, 0, key_value);
	}
	else
		key_value = ft_strdup(key_value);
	if (!validate_env_var_name(key_value, get_first_ind(key_value, '=', 0)))
		return (error_handler("minishell: export: 'key_value': not a \
			valid identifier"), 0);
	return (update_env_list(key_value, eq_ind, data, dollar_ind));
}
