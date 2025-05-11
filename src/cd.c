/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuknapek <zuknapek@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:04:19 by zuknapek          #+#    #+#             */
/*   Updated: 2025/05/11 19:54:25 by zuknapek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/env_vars.h"
#include "../libft/libft.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>


int	dir_check(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (!dir)
	{
		if (!access(path, F_OK))
		{
			if (access(path, R_OK) == 0)
				return (error_handler("bash: cd: {path}: Not a directory"), 0);
			else if (!access(path, R_OK) && chdir (path) == -1)
				return (error_handler(strerror(errno)), 0);
		}
		else
			return (error_handler("bash: cd: {path}: No such file or directory"), 0);
	}
	else
	{
		if (access(path, X_OK) == -1)
			return (error_handler("bash: cd: {path}: Permission denied"), closedir (dir), 0);
		else if (!access(path, X_OK) && chdir (path) == -1)
			return (error_handler(strerror(errno)), closedir (dir), 0);
	}
	return (closedir (dir), 1);
}


int	cd(char **input, t_data *data)
{
	char		*path;
	t_env_node	*node;

	path = NULL;
	if (input[1])
		return (error_handler("bash: cd: too many arguments"), 0);
	if (!input[0] || ((input[0][0] == '~') && ft_strlen(input[0]) == 1))
	{
		node = search_env_list(data, "HOME");
		if (!node)
			 return (error_handler("bash: cd: HOME not set"), 0);
		path = node->value;
	}
	else if (input[0][0] == '-' && ft_strlen(input[0]) == 1)
	{
		node = search_env_list(data, "OLDPWD");
		if (!node)
			 return (error_handler("bash: cd: OLDPWD not set"), 0);
		path = node->value;
	}
	else if (get_first_ind(input[0], '$', 0) != -1)
		path = echo_extend_env_value(data, ft_strdup(input[0]));
	else if (input[0] && input[0][0] != '~')
		path = input[0];
	ft_printf("path: %s\n", path);
	if (path)
		return (dir_check(path));
	return (0);
}
