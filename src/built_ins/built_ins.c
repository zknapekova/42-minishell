#include "env_vars.h"
#include "libft.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>


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

int	env_cmd(t_data *data, char **argv)
{
	if (arr_size(argv) > 1)
		return (error_handler("No options or arguments allowed in env command."), 0);
	if (!print_env_list(data))
		return (0);
	return (1);
}

int	pwd(char **argv)
{
	char	*cwd;
	char	*cwd_print;

	if (arr_size(argv) > 1)
		return (error_handler("No options or arguments allowed in pwd command."), 0);
	cwd = malloc(1024 * sizeof(char));
	if (!cwd)
		return (error_handler("malloc error"), 0);
	if (getcwd(cwd, 1024) == NULL)
		return (error_handler("getcwd failed"), free (cwd), 0);
	cwd_print = add_new_line(cwd);
	free(cwd);
	if (write(1, cwd_print, ft_strlen(cwd_print)) == -1)
		return (error_handler(strerror(errno)), free(cwd_print), 0);
	free(cwd_print);
	return (1);
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



