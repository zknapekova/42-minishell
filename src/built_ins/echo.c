/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:33:04 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/07/08 23:31:47 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_vars.h"
#include "libft.h"
#include "exec.h"
#include "built_ins.h"
#include <errno.h>
#include <string.h>

char	*echo_get_key_value(char *var_to_extend, t_data *data, char *key_value)
{
	char	*new_value_pre;
	char	*new_value_post;
	char	*new_value;
	int		dollar_ind;

	dollar_ind = get_first_ind(key_value, '$', 0);
	if (!search_env_list(data, var_to_extend))
	{
		new_value_pre = ft_substr(key_value, 0, dollar_ind);
		if (!new_value_pre)
			return (error_handler("malloc error"), NULL);
		new_value_post = get_new_val_post(key_value, dollar_ind, var_to_extend);
		if (!new_value_post)
			return (error_handler("malloc error"), NULL);
		new_value = ft_strjoin(new_value_pre, new_value_post);
	}
	else
		new_value = parse_env_value(search_env_list(data, var_to_extend), \
			key_value, dollar_ind, -1);
	if (!new_value)
		return (error_handler("malloc error"), NULL);
	if (get_first_ind(key_value, '$', 0) == -1)
		free(key_value);
	return (new_value);
}

char	*extend_env_value(t_data *data, char *key_value1)
{
	char	*var_to_extend;
	char	*new_key_value;
	char	*new_key_value2;
	char	*key_value;

	if (!key_value1)
		return (key_value1);
	new_key_value2 = NULL;
	key_value = replace_special_parameter(key_value1, data);
	if (get_first_ind(key_value, '$', 0) == -1)
		return (key_value);
	var_to_extend = get_extended_var(key_value);
	if (!var_to_extend)
		return (free (key_value), NULL);
	new_key_value = echo_get_key_value(var_to_extend, data, key_value);
	free (var_to_extend);
	free (key_value);
	key_value = NULL;
	if (!new_key_value)
		return (NULL);
	if (get_first_ind(new_key_value, '$', 0) != -1)
		new_key_value2 = extend_env_value(data, new_key_value);
	if (new_key_value2)
		return (new_key_value2);
	return (new_key_value);
}

// res stands for result, thank you norminette!
int	echo_cmd(char **input, t_data *data, t_ast *node)
{
	char	*res;
	int		i;
	t_arg	*temp_node;

	if (arr_size(input) == 1)
		return (write(1, "\n", 1), EXIT_SUCCESS);
	i = 0;
	temp_node = echo_set_node(&i, node, input[1]);
	normalize_n_flag(input);
	while (input[++i])
	{
		if (!ft_strcmp(input[i], "''"))
		{
			echo_write_space(input[i + 1], echo_set_fd(node), 1, NULL);
			continue ;
		}
		res = echo_preprocessing(input[i], temp_node, data);
		if (!res)
			return (error_handler(strerror(errno)), 1);
		write(echo_set_fd(node), res, ft_strlen(res));
		echo_write_space(input[i + 1], echo_set_fd(node), ft_strlen(res), res);
		if (temp_node)
			temp_node = temp_node->next;
	}
	return (echo_write_new_line(input[1], echo_set_fd(node)), EXIT_SUCCESS);
}

char	*extend_env_value_nf(t_data *data, char *key_value1)
{
	char	*var_to_extend;
	char	*new_key_value;
	char	*new_key_value2;
	char	*key_value;
	char	*key_value2;

	new_key_value2 = NULL;
	if (!key_value1)
		return (NULL);
	key_value2 = replace_special_parameter(key_value1, data);
	key_value = replace_empty(key_value2, data);
	if (get_first_ind(key_value, '$', 0) == -1)
		return (key_value);
	var_to_extend = get_extended_var(key_value);
	if (!var_to_extend)
		return (NULL);
	new_key_value = get_key_value_nf(var_to_extend, data, key_value);
	free (var_to_extend);
	if (!new_key_value)
		return (NULL);
	if (get_first_ind(new_key_value, '$', 0) != -1)
		new_key_value2 = extend_env_value_nf(data, new_key_value);
	if (new_key_value2)
		return (free (new_key_value), new_key_value2);
	return (new_key_value);
}

char	*get_key_value_nf(char *var_to_extend, t_data *data, char *key_value)
{
	char	*new_value_pre;
	char	*new_value_post;
	char	*new_value;
	int		dollar_ind;

	dollar_ind = get_first_ind(key_value, '$', 0);
	if (!search_env_list(data, var_to_extend))
	{
		new_value_pre = ft_substr(key_value, 0, dollar_ind);
		if (!new_value_pre)
			return (error_handler("malloc error"), NULL);
		new_value_post = get_new_val_post(key_value, dollar_ind, var_to_extend);
		if (!new_value_post)
			return (error_handler("malloc error"), free(new_value_pre), NULL);
		new_value = ft_strjoin(new_value_pre, new_value_post);
		free (new_value_pre);
		free (new_value_post);
	}
	else
		new_value = parse_env_value(search_env_list(data, var_to_extend), \
key_value, dollar_ind, -1);
	if (!new_value)
		return (error_handler(strerror(errno)), NULL);
	return (new_value);
}
