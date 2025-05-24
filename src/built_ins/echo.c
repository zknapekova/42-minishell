#include "../include/env_vars.h"
#include "../libft/libft.h"
#include <errno.h>
#include <string.h>

char	*echo_get_key_value(char *var_to_extend, t_data *data, char *key_value)
{
	char	*new_value;
	int		dollar_ind;

	dollar_ind = get_first_ind(key_value, '$', 0);
	if (!search_env_list(data, var_to_extend))
		new_value = ft_substr(key_value, 0, dollar_ind);
	else
		new_value = parse_env_value(search_env_list(data, var_to_extend), \
			key_value, dollar_ind, -1);
	if (!new_value)
		return (error_handler(strerror(errno)), NULL);
	if (get_first_ind(key_value, '$', 0) == -1)
		free(key_value);
	return (new_value);
}

char	*echo_extend_env_value(t_data *data, char *key_value)
{
	char	*var_to_extend;
	char	*new_key_value;
	char	*new_key_value2;
	int 	dollar_ind;

	new_key_value2 = NULL;
	dollar_ind = get_first_ind(key_value, '$', 0);
	var_to_extend = ft_substr(key_value, dollar_ind + 1, \
		get_first_non_alnum(key_value, dollar_ind + 1) - dollar_ind - 1);
	if (!var_to_extend)
		return (NULL);
	new_key_value = echo_get_key_value(var_to_extend, data, key_value);
	free (var_to_extend);
	free (key_value);
	if (!new_key_value)
		return (NULL);
	if (get_first_ind(new_key_value, '$', 0) != -1)
		new_key_value2 = echo_extend_env_value(data, new_key_value);
	if (new_key_value2)
		return (new_key_value2);
	return (new_key_value);
}

//in case of multiple strings these should be joined into 1, for instance input = "word1 word2"
int	echo(char *input, t_data *data, int n_param)
{
	int		dollar_ind;
	char	*result;

	dollar_ind = get_first_ind(input, '$', 0);
	if (dollar_ind != -1)
		result = echo_extend_env_value(data, ft_strdup(input));
	else
		result = ft_strdup(input);
	if (!result)
		return (error_handler(strerror(errno)), 0);
	if (write(1, result, ft_strlen(result)) == -1)
		return (error_handler(strerror(errno)), 0);
	if (!n_param)
	{
		if (write(1, "\n", 1) == -1)
			return (error_handler(strerror(errno)), 0);
	}
	return (free(result), 1);
}

// this function does not free the key_value
char	*extend_env_value_nf(t_data *data, char *key_value)
{
	char	*var_to_extend;
	char	*new_key_value;
	char	*new_key_value2;
	int 	dollar_ind;

	new_key_value2 = NULL;
	dollar_ind = get_first_ind(key_value, '$', 0);
	var_to_extend = ft_substr(key_value, dollar_ind + 1, \
		get_first_non_alnum(key_value, dollar_ind + 1) - dollar_ind - 1);
	if (!var_to_extend)
		return (NULL);
	new_key_value = echo_get_key_value(var_to_extend, data, key_value);
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