/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 20:07:47 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/05/24 20:49:28 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> //for NULL
#include <unistd.h> //for access //for getcwd
#include <limits.h> //for PATH_MAX
#include "libft.h"
#include "main.h"
#include "exec.h"

void	free_array(char **array);

char	*find_paths(t_data *data)
{
	char		*path_var;
	t_env_node	*path_node;

	path_var = NULL;
	path_node = search_env_list(data, "PATH");
	if (!path_node)
		return (error_handler("error finding PATH"), NULL);
	path_var = ft_strdup(path_node->value);
	return (path_var);
}

char	*get_full_path(char **paths, const char *cmd)
{
	char	*full_path1;
	char	*full_path2;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path1 = ft_strjoin(paths[i++], "/");
		if (!full_path1)
			return (error_handler("error joining path"), NULL);
		full_path2 = ft_strjoin(full_path1, cmd);
		if (!full_path2)
			return (free (full_path1), \
			error_handler("error joining path"), NULL);
		if (access(full_path2, X_OK) == 0)
			return (free (full_path1), full_path2);
		free (full_path1);
		free (full_path2);
	}
	return (NULL);
}

char	*get_path_from_env(const char *cmd, t_data *data)
{
	char	*path_var;
	char	**paths;
	char	*full_path;

	path_var = find_paths(data);
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ':');
	if (!paths)
		return (free (path_var), NULL);
	full_path = get_full_path(paths, cmd);
	free_array(paths);
	free (path_var);
	return (full_path);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free (array);
}

char	*get_exec_path(const char *cmd, t_data *data)
{
	char	*path;
	
	path = NULL;
	(void)data;
	if  (ft_strchr(cmd, '/'))
	{
		//path = get_path_from_env(cmd, data); //docasne, TODO: upravit
		path = ft_strdup(path);
		if (!path)
			return (error_handler("Error getting cmd path"), NULL);
		// ft_printf("Relative or absolute path found");
	}
	else
	{
		//path = get_path_from_env(cmd, data); //docasne, TODO: upravit
		path = ft_strdup(path);
		if (!path)
			return (error_handler("Error getting cmd path"), NULL);
	}
	return (path);
}

/*char	*get_path_from_path(const char *path, t_data *data)
{
	char	*abs_path;
	char	cwd[PATH_MAX];
	
	abs_path = NULL;
	if (path[0] == '/')
		return (ft_strdup(path));
	if (path[0] == '.')
		abs_path = get_normalized_path(path);
	(void)data;
	return (abs_path); //docasne, kvoli compileru
}*/

/*char	*get_normalized_path(const char *path)
{
	
}*/