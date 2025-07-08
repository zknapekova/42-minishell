#include "libft.h"
#include "main.h"
#include "env_vars.h"

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
