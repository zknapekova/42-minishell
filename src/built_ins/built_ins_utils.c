#include "main.h"
#include "libft.h"
#include "env_vars.h"
#include "exec.h"

void	execute_built_cmds(char **argv, t_data *data, int *status)
{
	if (get_first_ind(argv[0], '/', 0) != -1)
	{
		*status = EXIT_FAILURE;
		error_handler("Built-in command");
	}
	if (!ft_strcmp(argv[0], "echo"))
		*status = echo_cmd(argv, data);
	else if (!ft_strcmp(argv[0], "env"))
		*status = env_cmd(data, argv);
	else if (!ft_strcmp(argv[0], "unset"))
		*status = unset(data, argv);
	else if (!ft_strcmp(argv[0], "cd"))
		*status = cd(argv, data);
	else if (!ft_strcmp(argv[0], "pwd"))
		*status = pwd(argv);
	else if (!ft_strcmp(argv[0], "export"))
		*status = handle_new_env_value(data, argv[1]);
}

int	check_built_ins(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "unset") ||\
		!ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "cd") ||
		!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}