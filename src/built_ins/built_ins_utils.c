#include "main.h"
#include "libft.h"
#include "env_vars.h"
#include "exec.h"

int	ft_is_str_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '+' && str[i] != '-')
			return (0);
		if ((str[i] == '+' && str[i + 1] == '+') || (str[i] == '-' \
		&& str[i + 1] == '-'))
			return (0);
		i++;
	}
	return (1);
}

int	exit_cmd(char **argv)
{
	int	i;

	ft_printf("exit\n");
	i = 1;
	if (arr_size(argv) == 2)
	{
		if (!ft_is_str_digit(argv[1]))
			return (ft_eprintf("minishell: exit: %s numeric \
argument required\n", argv[1]), 2);
		return(ft_atoi(argv[1]));
	}
	if (arr_size(argv) > 2)
	{
		if (!ft_is_str_digit(argv[1]))
			return (ft_eprintf("minishell: exit: %s numeric \
argument required\n", argv[i]), 2);
		return (ft_eprintf("minishell: exit: too many arguments\n"), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	execute_built_cmds(char **argv, t_data *data, int *status, t_ast *node)
{
	if (get_first_ind(argv[0], '/', 0) != -1)
	{
		*status = EXIT_FAILURE;
		error_handler("Built-in command should not contain path");
		return ;
	}
	if (!ft_strcmp(argv[0], "echo"))
		*status = echo_cmd(argv, data, node);
	else if (!ft_strcmp(argv[0], "env"))
		*status = env_cmd(data, argv, node);
	else if (!ft_strcmp(argv[0], "unset"))
		*status = unset(data, argv);
	else if (!ft_strcmp(argv[0], "cd"))
		*status = cd(argv, data, node);
	else if (!ft_strcmp(argv[0], "pwd"))
		*status = pwd(node);
	else if (!ft_strcmp(argv[0], "exit"))
		*status = exit_cmd(argv);
	else if (!ft_strcmp(argv[0], "export"))
		*status = export(data, argv, node);
}

int	check_built_ins(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "unset") ||\
		!ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "cd") ||
		!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}
