#include "../include/env_vars.h"
#include "../libft/libft.h"
#include <errno.h>
#include <string.h>


int	print_env_list(t_data *data)
{
	t_env_node	*temp;
	char		*print_key_value;

	if (data->head)
	{
		temp = data->head;
		while (temp)
		{
			print_key_value = add_new_line(temp->key_value);
			if (!print_key_value)
				return (error_handler(strerror(errno)), 0);
			if (write(1, print_key_value, ft_strlen(print_key_value)) == -1)
				return (error_handler(strerror(errno)), free(print_key_value), 0);
			temp = temp->next;
			free(print_key_value);
			print_key_value = NULL;
		}
	}
	return (1);
}

int	export(t_data *data, char *input)
{
	if (input && !handle_new_env_value(data, input))
		return (0);
	if (!input && !print_env_list(data))
		return (0);
	return (1);
}

int	env_cmd(t_data *data)
{
	if (!print_env_list(data))
		return (0);
	return (1);
}

int	pwd(t_data *data)
{
	t_env_node	*res;
	char		*print_res;

	res = search_env_list(data, "PWD");
	if (!res)
		return (0);
	print_res = add_new_line(res->value);
	if (!print_res)
		return (0);
	if (write(1, print_res, ft_strlen(print_res)) == -1)
		return (error_handler(strerror(errno)), free(print_res), 0);
	return (free(print_res), 1);
}

int	unset(t_data *data, char **args)
{
	int	i;

	(void)data;
	if (args)
	{
		i = 0;
		while (args[i])
		{
			delete_node(data, args[i]);
			i++;
		}
	}
	return (1);
}



