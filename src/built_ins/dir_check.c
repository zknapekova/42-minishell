/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 02:02:26 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/07/09 02:02:27 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/env_vars.h"
#include "../libft/libft.h"
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int	check_and_alter(char *path, char *cmd, DIR *dir)
{
	if (access(path, X_OK) == -1)
		return (ft_eprintf("minishell:%s %s: Permission denied\n", cmd, \
			path), closedir(dir), EXIT_FAILURE);
	else if (!access(path, X_OK) && chdir(path) == -1)
		return (error_handler(strerror(errno)), closedir(dir),
			EXIT_FAILURE);
	return (closedir(dir), EXIT_SUCCESS);
}

int	dir_check(char *path, char *cmd)
{
	DIR	*dir;

	dir = opendir(path);
	if (!dir)
	{
		if (!access(path, F_OK))
		{
			if (access(path, R_OK) == 0)
				return (ft_eprintf("minishell:%s %s: Not a directory\n", cmd,
						path), EXIT_FAILURE);
			else if (!access(path, R_OK) && chdir(path) == -1)
				return (error_handler(strerror(errno)), EXIT_FAILURE);
		}
		else
			return (ft_eprintf("minishell:%s %s: No such file or directory\n",
					cmd, path), EXIT_FAILURE);
	}
	return (check_and_alter(path, cmd, dir));
}

int	is_dir(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir)
		return (closedir (dir), 1);
	return (closedir (dir), 0);
}
