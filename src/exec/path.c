
#include "libft.h"
#include "main.h"
#include "exec.h"
#include "parser_utils.h"
#include "env_vars.h"
#include <fcntl.h> //for open function
#include <unistd.h>
#include <errno.h>
#include <string.h>


// This function replaces ~ with $HOME variable and checks if file or folder exists/
// execve should be able to work with '.', '..' and '/' thats why they are not handled here
//free_path: 0 - dont free the path, 1 - free the path (it was mallocated before)
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
		return (ft_eprintf("minishell: %s: No such file or directory\n", result), NULL);
	return (result);
}

int	get_fd_file(char *path, t_redir_type type)
{
	int	fd;

	fd = -1;
	if (type == REDIR_INPUT)
	{
		if (access(path, R_OK) == -1)
			return (ft_eprintf("1.minishell: %s: %s", path, strerror(errno)), fd);
		fd = open(path, O_RDONLY);
	}
	else if (type == REDIR_OUTPUT)
		fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == REDIR_APPEND)
		fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		return (ft_eprintf("2.minishell: %s: %s", path, strerror(errno)), fd);
	return (fd);
}

// function to find command path or check if path to command is not already specified
char	*get_cmd_path(char *cmd, t_data *data)
{
	t_env_node	*node;
	char 		**paths;
	char		*com2;
	int			j;
	char		*path;

	if (!access(cmd, F_OK|X_OK))
		return (ft_strdup(cmd));
	node = search_env_list(data, "PATH");
	if (!node)
		return (error_handler("Env variable PATH not set"), NULL);
	paths = ft_split(node->value, ':');
	if (!paths)
		return (error_handler("malloc error"), NULL);
	com2 = ft_strjoin("/", cmd);
	if (!com2)
		return (error_handler("malloc error"), NULL);
	j = 0;
	while (paths[j])
	{
		path = ft_strjoin(paths[j], com2);
		if (!path)
			return (error_handler("malloc error"), free (com2), NULL);
		if (access(path, X_OK) == 0)
			return (free(com2), free(paths), path);
		free(path);
		j++;
	}
	return (NULL);
}