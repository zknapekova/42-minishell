#include "libft.h"
#include "main.h"
#include "exec.h"
#include "parser_utils.h"
#include "env_vars.h"
#include <fcntl.h> //for open function
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>

// This function replaces ~ with $HOME variable
//and checks if file or folder exists. execve
//should be able to work with '.', '..' and '/'
//thats why they are not handled here.
//free_path: 0 - dont free the path, 1 - free the path
char	*handle_path(char *path, int free_path, int folder, int existence_check)
{
	char	*result;

	result = NULL;
	if (get_first_ind(path, '~', 0) != -1)
		result = replace_tilde(path, get_first_ind(path, '~', 0));
	else
		result = ft_strdup(path);
	if (!result)
	{
		if (free_path)
			free(path);
		return (error_handler("malloc: Error when replacing ~"), NULL);
	}
	if (free_path)
		free(path);
	if (folder)
	{
		if (!dir_check(result, ""))
			return (free(result), NULL);
	}
	else if (!folder && access(result, F_OK) == -1 && existence_check == 1)
		return (ft_eprintf("minishell: %s: No such file \
or directory\n", result), NULL);
	return (result);
}

int	get_fd_file(char *path, t_redir_type type)
{
	int	fd;

	fd = -1;
	if (type == REDIR_INPUT)
	{
		if (access(path, R_OK) == -1)
			return (ft_eprintf("minishell: %s: %s\n", path, \
			strerror(errno)), fd);
		fd = open(path, O_RDONLY);
	}
	else if (type == REDIR_OUTPUT)
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == REDIR_APPEND)
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		return (ft_eprintf("minishell: %s: %s\n", path, strerror(errno)), fd);
	return (fd);
}

char	**get_paths(t_data *data)
{
	t_env_node	*node;
	char 		**paths;

	node = search_env_list(data, "PATH");
	if (!node)
		return (error_handler("Env variable PATH not set"), NULL);
	paths = ft_split(node->value, ':');
	if (!paths)
		return (error_handler("malloc error"), NULL);
	return (paths);
}

char	*find_cmd_path(char *cmd, char *com2, t_data *data, int *status)
{
	char 		**paths;
	int			j;
	char		*path;

	paths = get_paths(data);
	if (!paths)
		return (*status = 1, NULL);
	j = -1;
	while (paths[++j])
	{
		path = ft_strjoin(paths[j], com2);
		if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
			return (free(com2), free(paths), path);
		else if (access(path, F_OK) == 0 && access(path, X_OK) != 0)
			return (free(com2), free(paths), *status = 126, path);
		free(path);
		free(paths[j]);
	}
	free(com2);
	free(paths);
	*status = 127;
	if (get_first_ind(cmd, '/', 0) != -1)
		return (ft_eprintf("minishell: %s: No such file or directory\n", cmd), NULL);
	return (ft_eprintf("%s: command not found\n", cmd), NULL);
}


char	*get_cmd_path(char *cmd, t_data *data, int *status)
{
	char		*com2;

	if (get_first_ind(cmd, '/', 0) != -1)
	{
		if (is_dir(cmd))
			return (*status = 126, ft_eprintf("minishell: %s: Is a \
directory\n", cmd), NULL);
	}
	if (!access(cmd, F_OK) && !access(cmd, X_OK) && !is_dir(cmd))
		return (ft_strdup(cmd));
	else if (!access(cmd, F_OK) && access(cmd, X_OK) != 0 && \
	!is_dir(cmd) && get_first_ind(cmd, '.', 1) == -1)
		return (*status = 126, ft_eprintf("minishell: %s: Permission \
denied\n", cmd), NULL);
	com2 = ft_strjoin("/", cmd);
	if (!com2)
		return (error_handler("malloc error"), *status = 1, NULL);
	return (find_cmd_path(cmd, com2, data, status));
}
