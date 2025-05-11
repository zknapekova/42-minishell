#include "../include/env_vars.h"
#include "../libft/libft.h"
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>


// chdir(~)  returns -1, chdir(..) and chdir(.) works ok
int	cd(char **input, t_data *data)
{
	char		*path;
	t_env_node	node;
	DIR			*dir;

	if (input[1])
		return (error_handler("bash: cd: too many arguments"), 0);
	if (!input[0] || input[0] == '~')
	{
		node = search_env_list(data, "HOME");
		if (!node)
			 return (error_handler("bash: cd: HOME not set"), 0);
		path = node->value;
	}
	else if (input[0] && input[0] != '~')
		path = input[0];
	dir = opendir(path);
	if (!dir)
	{}



	int err = chdir (path);
	ft_putnbr_fd(err, 1);
	return (1);
}