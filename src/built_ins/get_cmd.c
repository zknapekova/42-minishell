/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 20:07:47 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/05/23 15:13:00 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> //for NULL
#include <unistd.h> //for access
#include "libft.h"
#include "main.h"

// search_env_list

char	*find_path(t_data *data)
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
			return (NULL);
		full_path2 = ft_strjoin(full_path1, cmd);
		if (!full_path2)
		{
			free (full_path1);
			return (NULL);
		}
		if (access(full_path2, X_OK) == 0)
		{
			free (full_path1);
			return (full_path2);
		}
		free (full_path1);
		free (full_path2);
	}
	return (NULL);
}

char	*find_executable(const char *cmd, t_data *data)
{
	char	*path_var;
	char	**paths;
	char	*full_path;

	path_var = find_path(data);
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ':');
	if (!paths)
		return (NULL);
	full_path = get_full_path(paths, cmd);
	free_array(paths);
	return (full_path);
}

int	get_commands(int argc, char **argv, t_pipex *pipex, char **envp)
{
	int		i;
	int		offset;
	char	**temp;

	if (!alloc_cmd_paths(pipex) || !alloc_cmd_args(pipex))
		return (0);
	offset = 2 + pipex->here_doc;
	i = -1;
	while (++i + offset < argc - 1)
	{
		temp = ft_split(argv[i + offset], ' ');
		if (!temp)
			return (0);
		pipex->cmd_paths[i] = find_executable(temp[0], envp);
		if (!pipex->cmd_paths[i] || !get_args(pipex, temp, i))
		{
			if (!pipex->cmd_paths[i])
				ft_printf("%s: %s: command not found\n", argv[0], temp[0]);
			free_array(temp);
			return (0);
		}
		free_array(temp);
	}
	return (1);
}
