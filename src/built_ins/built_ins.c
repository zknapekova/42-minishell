/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 23:41:44 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/07/09 18:15:54 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_vars.h"
#include "libft.h"
#include "built_ins.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>

int	print_env_list(t_data *data, t_ast *node, int export)
{
	t_env_node	*temp;
	char		*print_key_value;
	int			fd;

	fd = echo_set_fd(node);
	if (data->head)
	{
		temp = data->head;
		while (temp)
		{
			if (ft_print_env(temp->key_value))
			{
				print_key_value = add_new_line(temp->key_value);
				if (!print_key_value)
					return (error_handler(strerror(errno)), 0);
				if (export)
					write(fd, "declare -x ", 11);
				write(fd, print_key_value, ft_strlen(print_key_value));
				free(print_key_value);
				print_key_value = NULL;
			}
			temp = temp->next;
		}
	}
	return (1);
}

int	export(t_data *data, char **input, t_ast *node)
{
	int	i;

	i = 1;
	if (!input[i] && !print_env_list(data, node, 1))
		return (EXIT_FAILURE);
	while (input[i])
	{
		if (!handle_new_env_value(data, input[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	env_cmd(t_data *data, char **argv, t_ast *node)
{
	if (arr_size(argv) > 1)
		return (error_handler("No options or arguments \
allowed in env command."), EXIT_FAILURE);
	if (!print_env_list(data, node, 0))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	pwd(t_ast *node)
{
	char	*cwd;
	char	*cwd_print;
	int		fd;

	cwd = malloc(1024 * sizeof(char));
	if (!cwd)
		return (error_handler("malloc error"), EXIT_FAILURE);
	if (getcwd(cwd, 1024) == NULL)
		return (error_handler("getcwd failed"), free (cwd), EXIT_FAILURE);
	cwd_print = add_new_line(cwd);
	free(cwd);
	fd = 1;
	if (node->cmd_data->fd_file_out != -1 \
		&& node->cmd_data->fd_pipe_in == -1 \
		&& node->cmd_data->fd_pipe_out == -1)
		fd = node->cmd_data->fd_file_out;
	if (write(fd, cwd_print, ft_strlen(cwd_print)) == -1)
		return (error_handler(strerror(errno)), free(cwd_print), EXIT_FAILURE);
	free(cwd_print);
	return (EXIT_SUCCESS);
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
			if (args[i][0] == '-')
				return (ft_eprintf("invalid option"), 2);
			if (args[i][0] != '?')
				delete_node(data, args[i]);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
