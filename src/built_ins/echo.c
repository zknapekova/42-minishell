#include "../include/env_vars.h"
#include "../libft/libft.h"
#include "exec.h"
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
		new_value_post = ft_substr(key_value, dollar_ind + ft_strlen(var_to_extend) + 1, \
			ft_strlen(key_value) - dollar_ind - ft_strlen(var_to_extend));
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
	int 	dollar_ind;

	if (key_value1)
	{
		new_key_value2 = NULL;
		key_value = replace_special_parameter(key_value1, data);
		dollar_ind = get_first_ind(key_value, '$', 0);
		if (dollar_ind > -1)
		{
			var_to_extend = ft_substr(key_value, dollar_ind + 1, \
					get_first_non_alnum(key_value, dollar_ind + 1) - dollar_ind - 1);
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
	}
	return (key_value1);
}

//in case of multiple strings these should be joined into 1, for instance input = "word1 word2"
int	echo_cmd(char **input, t_data *data)
{
	char	*result;
	int		i;

	if (arr_size(input) == 1)
	{
		write(1, "\n", 1);
		return (EXIT_SUCCESS);
	}
	i = 1;
	if (!ft_strcmp(input[1], "-n"))
		i = 2;
	while (input[i])
	{
		if (get_first_ind(input[i], '~', 0) > -1 || get_first_ind(input[i], '$', 0) > -1)
			result = extend_env_value(data, replace_tilde(input[i], get_first_ind(input[i], '~', 0)));
		else
			result = ft_strdup(input[i]);
		if (!result)
			return (error_handler(strerror(errno)), EXIT_FAILURE);
		if (write(1, result, ft_strlen(result)) == -1)
			return (error_handler(strerror(errno)), free(result), EXIT_FAILURE);
		if (ft_strlen(result) > 0 && input[i + 1])
			write(1, " ", 1);
		free(result);
		i++;
	}
	if (ft_strcmp(input[1], "-n") != 0)
	{
		if (write(1, "\n", 1) == -1)
			return (error_handler(strerror(errno)), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

char	*extend_env_value_nf(t_data *data, char *key_value1)
{
	char	*var_to_extend;
	char	*new_key_value;
	char	*new_key_value2;
	char	*key_value;
	int 	dollar_ind;

	new_key_value2 = NULL;
	key_value = replace_special_parameter(key_value1, data);
	dollar_ind = get_first_ind(key_value, '$', 0);
	var_to_extend = ft_substr(key_value, dollar_ind + 1, \
			get_first_non_alnum(key_value, dollar_ind + 1) - dollar_ind - 1);
	if (!var_to_extend)
		return (NULL);
	new_key_value = get_key_value_nf(var_to_extend, data, key_value);
	free (var_to_extend);
	// free (key_value);
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
		new_value_post = ft_substr(key_value, dollar_ind + ft_strlen(var_to_extend) + 1, \
			ft_strlen(key_value) - dollar_ind - ft_strlen(var_to_extend));
		if (!new_value_post)
			return (error_handler("malloc error"), NULL);
		new_value = ft_strjoin(new_value_pre, new_value_post);
	}
	else
		new_value = parse_env_value(search_env_list(data, var_to_extend), \
			key_value, dollar_ind, -1);
	if (!new_value)
		return (error_handler(strerror(errno)), NULL);
	// if (get_first_ind(key_value, '$', 0) == -1)
	// 	free(key_value);
	return (new_value);
}
