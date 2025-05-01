/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_ops.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuknapek <zuknapek@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:47:56 by zuknapek          #+#    #+#             */
/*   Updated: 2025/04/27 19:05:22 by zuknapek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/env_vars.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int	extend_env_value(t_data *data, char *key_value, char *var_name, t_env_node *node_to_update)
{
	char		*var_to_extend;
	char		*new_key_value;
	int		    eq_ind;
	int		    dollar_ind;

	update_dollar_eq_ind(&dollar_ind, &eq_ind, 0, key_value);
	var_to_extend = ft_substr(key_value, dollar_ind + 1, get_first_occurr_non_alnum(key_value, dollar_ind + 1) - dollar_ind - 1);
	if (!var_to_extend)
	    return(error_handler(strerror(errno)), 0);
	new_key_value = get_key_value(var_to_extend, data, key_value, var_name);
	free(var_to_extend);
	free(key_value);
    if (!new_key_value)
			return(error_handler(strerror(errno)), 0);
	if (get_first_ind(new_key_value, '$', 0) == -1)
	{
	    if (!handle_new_node(node_to_update, data, new_key_value))
	        return (0);
	}
	else
	    extend_env_value(data, new_key_value, var_name, node_to_update);
	return (1);
}


char    *get_extended_var_name(char *key_value, int dollar_ind, int eq_ind, t_data *data)
{
	char		*var_to_extend;
	t_env_node  *extend_env_node;
	char        *temp_key_value;
	char        *var_name;

	if (get_first_ind(key_value, '$', dollar_ind + 1) > eq_ind)
        var_to_extend = ft_substr(key_value, dollar_ind + 1, eq_ind - dollar_ind - 1);
    else
        var_to_extend = ft_substr(key_value, dollar_ind + 1, get_first_ind(key_value, '$', \
                dollar_ind + 1) - dollar_ind - 1);
    if (!var_to_extend)
        return(error_handler(strerror(errno)), NULL);
    extend_env_node = search_env_list(data, var_to_extend);
	free(var_to_extend);
    temp_key_value = ft_substr(key_value, 0, dollar_ind);
    if (!temp_key_value)
        return (error_handler(strerror(errno)), NULL);
    if (extend_env_node)
    {
        var_name = ft_strjoin(temp_key_value, extend_env_node->value);
		if (!var_name)
		    return (free(temp_key_value), error_handler(strerror(errno)), NULL);
		return (free(temp_key_value), var_name);
    }
    else
        return (temp_key_value);
}


char    *extend_var_name(int dollar_ind, int eq_ind, t_data *data, char *key_value)
{
    char		*var_name;
	char        *temp_key_value2;
    char        *new_key_value;
	char        *new_key_value2;

	var_name = get_extended_var_name(key_value, dollar_ind, eq_ind, data);
	if (!var_name)
	    return (NULL);
    if (get_first_ind(key_value, '$', dollar_ind + 1) < eq_ind)
        temp_key_value2 = ft_substr(key_value, get_first_ind(key_value, '$', dollar_ind + 1), \
                ft_strlen(key_value) - get_first_ind(key_value, '$', dollar_ind + 1));
    else
        temp_key_value2 = ft_substr(key_value, eq_ind, ft_strlen(key_value) - eq_ind);
    if (!temp_key_value2)
        return (error_handler(strerror(errno)), NULL);
    new_key_value = ft_strjoin(var_name, temp_key_value2);
    if (!new_key_value)
        return (free(temp_key_value2), error_handler(strerror(errno)), NULL);
    free(temp_key_value2);
    update_dollar_eq_ind(&dollar_ind, &eq_ind, 0, new_key_value);
    if (dollar_ind < eq_ind)
    {
        new_key_value2 = extend_var_name(dollar_ind, eq_ind, data, new_key_value);
        return (free(new_key_value), free(var_name), new_key_value2);
    }
	return (free(var_name), new_key_value);
}

int update_env_list(char *key_value, int eq_ind, t_data *data, int dollar_ind)
{
    char		*var_name;
    t_env_node  *node_to_update;

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
	if (eq_ind == -1 || (eq_ind != -1 && !validate_env_var_name(key_value, eq_ind)))
	    return (error_handler("minishell: export: '{key_value}': not a valid identifier"), 0); // pouzit fciu ft_eprintf()
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
        return (error_handler("minishell: export: 'key_value': not a valid identifier"), 0);
    return (update_env_list(key_value, eq_ind, data, dollar_ind));
}



