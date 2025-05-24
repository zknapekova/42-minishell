/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 20:07:47 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/05/24 18:38:43 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> //for NULL
#include <unistd.h> //for access
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

char	*get_exec_path(const char *cmd, t_data *data)
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