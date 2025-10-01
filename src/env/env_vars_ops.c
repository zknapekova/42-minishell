/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_ops.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:47:56 by zuknapek          #+#    #+#             */
/*   Updated: 2025/06/08 16:24:27 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/env_vars.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int	export_extend_env_value(t_data *data, char *key_value, char *var_name, \
	t_env_node *node_to_update)
{
	char	*var_to_extend;
	char	*new_key_value;
	int		eq_ind;
	int		dollar_ind;

	update_dollar_eq_ind(&dollar_ind, &eq_ind, 0, key_value);
	var_to_extend = ft_substr(key_value, dollar_ind + 1, \
		get_first_non_alnum(key_value, dollar_ind + 1) - dollar_ind - 1);
	if (!var_to_extend)
		return (error_handler(strerror(errno)), 0);
	new_key_value = get_key_value(var_to_extend, data, key_value, var_name);
	free (var_to_extend);
	free (key_value);
	if (!new_key_value)
		return (error_handler(strerror(errno)), 0);
	if (get_first_ind(new_key_value, '$', 0) == -1 && eq_ind != -1)
	{
		if (!handle_new_node(node_to_update, data, new_key_value))
			return (0);
	}
	else
		export_extend_env_value(data, new_key_value, var_name, node_to_update);
	return (1);
}

char	*get_var_to_extend(char *key_value, int dollar_ind, int eq_ind)
{
	char		*var_to_extend;

	if (get_first_ind(key_value, '$', dollar_ind + 1) > eq_ind)
		var_to_extend = ft_substr(key_value, dollar_ind + 1, \
			eq_ind - dollar_ind - 1);
	else
		var_to_extend = ft_substr(key_value, dollar_ind + 1, \
		get_first_ind(key_value, '$', dollar_ind + 1) - dollar_ind - 1);
	if (!var_to_extend)
		return (error_handler(strerror(errno)), NULL);
	return (var_to_extend);
}

char	*get_temp_key_value(char *key_value, int dollar_ind, int eq_ind, \
	char *var_name)
{
	char	*temp_key_value2;
	char	*new_key_value;

	if (get_first_ind(key_value, '$', dollar_ind + 1) < eq_ind)
		temp_key_value2 = ft_substr(key_value, get_first_ind(key_value, '$', \
	dollar_ind + 1), ft_strlen(key_value) - get_first_ind(key_value, \
	'$', dollar_ind + 1));
	else
		temp_key_value2 = ft_substr(key_value, eq_ind, \
			ft_strlen(key_value) - eq_ind);
	if (!temp_key_value2)
		return (error_handler(strerror(errno)), NULL);
	new_key_value = ft_strjoin(var_name, temp_key_value2);
	if (!new_key_value)
		return (free(temp_key_value2), error_handler(strerror(errno)), NULL);
	free(temp_key_value2);
	return (new_key_value);
}

char	*get_extended_var_name(char *key_value, int dollar_ind, \
			int eq_ind, t_data *data)
{
	char		*var_to_extend;
	t_env_node	*extend_env_node;
	char		*temp_key_value;
	char		*var_name;

	var_to_extend = get_var_to_extend(key_value, dollar_ind, eq_ind);
	if (!var_to_extend)
		return (NULL);
	extend_env_node = search_env_list(data, var_to_extend);
	free(var_to_extend);
	temp_key_value = ft_substr(key_value, 0, dollar_ind);
	if (!temp_key_value)
		return (error_handler(strerror(errno)), NULL);
	if (extend_env_node)
	{
		var_name = ft_strjoin(temp_key_value, extend_env_node->value);
		if (!var_name)
			return (free(temp_key_value), error_handler(strerror(errno)), \
			NULL);
		return (free(temp_key_value), var_name);
	}
	else
		return (temp_key_value);
}

char	*extend_var_name(int dollar_ind, int eq_ind, t_data *data, \
	char *key_value)
{
	char	*var_name;
	char	*new_key_value;
	char	*new_key_value2;

	var_name = get_extended_var_name(key_value, dollar_ind, eq_ind, data);
	if (!var_name)
		return (NULL);
	new_key_value = get_temp_key_value(key_value, dollar_ind, eq_ind, var_name);
	update_dollar_eq_ind(&dollar_ind, &eq_ind, 0, new_key_value);
	if (dollar_ind < eq_ind)
	{
		new_key_value2 = extend_var_name(dollar_ind, eq_ind, data, \
			new_key_value);
		return (free(new_key_value), free(var_name), new_key_value2);
	}
	return (free(var_name), new_key_value);
}
