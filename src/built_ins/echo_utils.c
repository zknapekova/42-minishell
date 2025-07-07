/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 21:40:33 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/07/06 23:15:25 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"
#include "env_vars.h"


t_bool	is_n_flag(char *str);

void	normalize_n_flag(char **input)
{
	int		read;
	int		write;
	t_bool	found_n_flag;

	read = 1;
	write = 1;
	found_n_flag = false;
	while (input[read] && is_n_flag(input[read]))
	{
		free(input[read]);
		read++;
		found_n_flag = true;
	}
	if (found_n_flag == true)
		input[write++] = ft_strdup("-n");
	while (input[read])
		input[write++] = input[read++];
	input[write] = NULL;
}

t_bool	is_n_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (false);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

char *echo_preprocessing(char *str, t_arg *temp_node, t_data *data)
{
	char	*temp;
	char	*result;

	if (get_first_ind(str, '~', 0) > -1 && str[get_first_ind(str, '~', 0) + 1] \
	!='\0' && str[get_first_ind(str, '~', 0) + 1] != '/')
		result = ft_strdup(str);
	else if (get_first_ind(str, '~', 0) > -1 && temp_node->quote_type == QUOTE_NONE)
	{
		temp = replace_tilde(str, get_first_ind(str, '~', 0));
		result = extend_env_value(data, ft_strdup(temp));
		free(temp);
	}
	else
		result = ft_strdup(str);
	return (result);
}

int	echo_set_fd(t_ast *node)
{
	int	fd;

	fd = 1;
	if (node->cmd_data->fd_file_out != -1 && \
	node->cmd_data->fd_pipe_out == -1 && node->cmd_data->fd_pipe_in == -1)
		fd = node->cmd_data->fd_file_out;
	return (fd);
}


void	echo_write_new_line(char *str, int fd)
{
	if (ft_strcmp(str, "-n") != 0)
		write(fd, "\n", 1);
}
