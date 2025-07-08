#include "env_vars.h"
#include "libft.h"
#include "main.h"

void	echo_write_space(char *str, int fd, int ind, char *free_str)
{
	if (str && ind > 0)
		write(fd, " ", 1);
	if (free_str)
		free(free_str);
}

t_arg	*echo_set_node(int *i, t_ast *node, char *str)
{
	t_arg	*temp_node;

	temp_node = NULL;
	if (node && node->cmd_data && node->cmd_data->args)
	{
		temp_node = node->cmd_data->args->next;
		if (!ft_strcmp(str, "-n"))
		{
			*i = 1;
			temp_node = node->cmd_data->args->next->next;
		}
	}
	return (temp_node);
}

char	*get_extended_var(char *key_value)
{
	char	*var_to_extend;

	var_to_extend = ft_substr(key_value, get_first_ind(key_value, '$', 0) + 1,
			get_first_non_alnum(key_value, get_first_ind(key_value, '$', 0) + 1)
			- get_first_ind(key_value, '$', 0) - 1);
	return (var_to_extend);
}

char	*get_new_val_post(char *key_value, int dollar_ind, char *var_to_extend)
{
	char	*new_val_post;

	new_val_post = ft_substr(key_value, dollar_ind + ft_strlen(var_to_extend)
			+ 1, ft_strlen(key_value) - dollar_ind - ft_strlen(var_to_extend));
	return (new_val_post);
}