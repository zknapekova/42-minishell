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

char	*parse_env_value(t_env_node *node, char *key_value, int dollar_ind, int eq_ind)
{
	char		*new_value;
	char		*temp;
	char		*temp0;
	char		*substr;

	if (dollar_ind > eq_ind)
	    temp0 = ft_substr(key_value, eq_ind + 1,  dollar_ind - eq_ind - 1);
	if (!temp0)
		return(error_handler(strerror(errno)), NULL);
    printf("temp0: %s\n", temp0);
	temp = ft_strjoin(temp0, node->value);
	if (!temp)
		return (free(temp0), error_handler(strerror(errno)), NULL);
	printf("temp: %s\n", temp);
	free(temp0);
	substr = ft_substr(key_value, dollar_ind + ft_strlen(node->key) + 1, ft_strlen(key_value) - dollar_ind + ft_strlen(node->key) + 1);
	printf("substr: %s\n", substr);
	if (!substr)
		return (free(temp), error_handler(strerror(errno)), NULL);
	new_value = ft_strjoin(temp, substr);
	if (!new_value)
		return (free(temp), free(substr), error_handler(strerror(errno)), NULL);
	free(substr);
	free(temp);
	return (new_value);
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
			if (ft_strncmp(temp->key, key, len) == 0 && len == ft_strlen(temp->key))
				return (temp);
			temp = temp->next;
		}
	}
	return (NULL);
}

char *get_key_value(char *var_to_extend, t_data *data, char *key_value, char *var_name)
{
    t_env_node	*extend_env_node;
    char		*temp_key_value;
	char		*new_key_value;
	char		*new_value;
    int         dollar_ind;

    dollar_ind = get_first_occurr_index(key_value, '$', 0);
    printf("dollar index is:%d\n", dollar_ind);
    extend_env_node = search_env_list(data, var_to_extend);
    if (!extend_env_node)
    {
        temp_key_value = ft_substr(key_value, 0, dollar_ind);
        new_value = ft_substr(key_value, get_first_occurr_non_alnum(key_value, dollar_ind + 1), \
                ft_strlen(key_value) - get_first_occurr_non_alnum(key_value, dollar_ind + 1));
    }
    else
	{
		temp_key_value = ft_strjoin(var_name, "=");
		new_value = parse_env_value(extend_env_node, key_value, dollar_ind, \
		                get_first_occurr_index(key_value, '=', 0));
	}
	printf("new_value:%s\n", new_value);
	new_key_value = ft_strjoin(temp_key_value, new_value);
	printf("n1ew_key_value:%s\n", new_key_value);
	printf("check1");
	free(temp_key_value);
	free(new_value);

	if (get_first_occurr_index(key_value, '$', 0) == -1)
	{
	    free(key_value);
	}

	return (new_key_value);
}

int	extend_env_value(t_data *data, char *key_value, char *var_name, t_env_node *node_to_update)
{
	char		*var_to_extend;
	char		*new_key_value;
	int		    eq_ind;
	int		    dollar_ind;

	dollar_ind = get_first_occurr_index(key_value, '$', 0);
	eq_ind = get_first_occurr_index(key_value, '=', 0);
	var_to_extend = ft_substr(key_value, dollar_ind + 1, get_first_occurr_non_alnum(key_value, dollar_ind + 1) - dollar_ind - 1);
	if (!var_to_extend)
	    return(error_handler(strerror(errno)), 0);
	new_key_value = get_key_value(var_to_extend, data, key_value, var_name);
	free(var_to_extend);
	free(key_value);
    if (!new_key_value)
			return(error_handler(strerror(errno)), 0);
	if (!node_to_update && get_first_occurr_index(new_key_value, '$', 0) == -1)
	{
	    if (!add_env(data, new_key_value))
	    {
	        return(error_handler(strerror(errno)), 0);
	    }
	}
	else if (node_to_update && get_first_occurr_index(new_key_value, '$', 0) == -1)
	    update_node(node_to_update, new_key_value, eq_ind);
	if (get_first_occurr_index(new_key_value, '$', dollar_ind) != -1)
	    extend_env_value(data, new_key_value, var_name, node_to_update);

	return (1);
}

char    *extend_var_name(int dollar_ind, int eq_ind, t_data *data, char *key_value)
{
    char		*var_to_extend;
    t_env_node  *extend_env_node;
    char		*var_name0;
    char		*var_name;
    char        *temp_key_value;
    char        *new_key_value;

    if (get_first_occurr_index(key_value, '$', dollar_ind + 1) > eq_ind)
        var_to_extend = ft_substr(key_value, dollar_ind + 1, eq_ind - dollar_ind - 1);
    else
        var_to_extend = ft_substr(key_value, dollar_ind + 1, eq_ind - get_first_occurr_index(key_value, '$', dollar_ind + 1) - 1);
    if (!var_to_extend)
        return(error_handler(strerror(errno)), NULL);
    extend_env_node = search_env_list(data, var_to_extend);
    temp_key_value = ft_substr(key_value, 0, dollar_ind);
    if (!temp_key_value)
        return(error_handler(strerror(errno)), NULL);
    if (extend_env_node)
    {
        var_name0 = ft_strjoin(temp_key_value, extend_env_node->value);
        if (get_first_occurr_index(key_value, '$', dollar_ind + 1) < eq_ind)
            var_name = ft_strjoin(var_name0, ft_substr(key_value, get_first_occurr_index(key_value, '$', dollar_ind + 1), eq_ind - get_first_occurr_index(key_value, '$', dollar_ind + 1)));
        else
            var_name = var_name0;
    }
    else
        var_name = temp_key_value;
    new_key_value = ft_strjoin(var_name, ft_substr(key_value, eq_ind, ft_strlen(key_value) - eq_ind));
    dollar_ind = get_first_occurr_index(new_key_value, '$', dollar_ind + 1);
    if (dollar_ind < get_first_occurr_index(new_key_value, '=', 0))
        var_name = extend_var_name(dollar_ind, get_first_occurr_index(new_key_value, '=', 0), data, new_key_value);
    return (var_name);
}

//This function should be called when prompt contains "export"
int	handle_new_env_value(t_data *data, char *key_value)
{
	int		eq_ind;
	int		dollar_ind;
	char		*var_name;
	t_env_node  *node_to_update;

	dollar_ind = get_first_occurr_index(key_value, '$', 0);
	eq_ind = get_first_occurr_index(key_value, '=', 0);
	if (eq_ind != -1)
	{
        var_name = ft_substr(key_value, 0, eq_ind);
        if (!var_name)
            return (error_handler(strerror(errno)), 0);
       if (!validate_env_var_name(var_name))
        {
            return (free(var_name), error_handler("minishell: export: 'key_value': not a valid identifier"), 0);
        }
        if (dollar_ind != -1 && dollar_ind < eq_ind)
        {
            var_name = extend_var_name(dollar_ind, eq_ind, data, key_value);
            key_value = ft_strjoin(var_name, ft_substr(key_value, eq_ind, ft_strlen(key_value) - eq_ind));
            dollar_ind = get_first_occurr_index(key_value, '$', 0);
            eq_ind = get_first_occurr_index(key_value, '=', 0);
        }
        printf("key_value: %s\n", key_value);
	    node_to_update = search_env_list(data, var_name);
	    if (!node_to_update && dollar_ind == -1)
	        add_env(data, ft_strdup(key_value));
	    else if (node_to_update && dollar_ind == -1)
            update_node(node_to_update, ft_strdup(key_value), eq_ind);
	    else if (dollar_ind != -1)
	    {
	        if (!extend_env_value(data, ft_strdup(key_value), var_name, node_to_update))
			    return (free(var_name), 0);
	    }
	    free(var_name);
	}
	else if (eq_ind == -1)
	    return (error_handler("minishell: export: '{key_value}': not a valid identifier"), -1); // pouzit fciu ft_eprintf()
	return (1);
}