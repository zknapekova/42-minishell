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
		i++;
	}
	return (1);
}

int	exit_cmd(char **argv)
{
	ft_printf("exit\n");
	if (arr_size(argv) > 2)
		return (ft_eprintf("minishell: exit: too many arguments\n"), EXIT_FAILURE);
	if (arr_size(argv) == 2)
	{
		if (!ft_is_str_digit(argv[1]))
			return (ft_eprintf("minishell: exit: %s numeric argument required\n", argv[1]), 2);
		return(ft_atoi(argv[1]));
	}
	return (EXIT_SUCCESS);
}

void	execute_built_cmds(char **argv, t_data *data, int *status)
{
	if (get_first_ind(argv[0], '/', 0) != -1)
	{
		*status = EXIT_FAILURE;
		error_handler("Built-in command should not contain path");
		return ;
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
		*status = pwd();
	else if (!ft_strcmp(argv[0], "export"))
		*status = export(data, argv[1]);
	else if (!ft_strcmp(argv[0], "exit"))
		*status = exit_cmd(argv);
}

int	check_built_ins(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "unset") ||\
		!ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "cd") ||
		!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

char	*replace_special_parameter(char *str, t_data *data)
{
	int	i;
	t_env_node	*node;
	char		*pre_str;
	char		*post_str;
	char		*temp_str;
	char		*replaced_str;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			node = search_env_list(data, "?");
			pre_str = ft_substr(str, 0, i);
			if (!pre_str)
				return (error_handler("malloc error"), NULL);
			temp_str = ft_strjoin(pre_str, node->value);
			if (!temp_str)
				return (free(pre_str), error_handler("malloc error"), NULL);
			free(pre_str);
			pre_str = NULL;
			post_str = ft_substr(str, i + 2, ft_strlen(str) - (i + 1));
			if (!post_str)
				return (error_handler("malloc error"), NULL);
			pre_str = ft_strjoin(temp_str, post_str);
			if (!pre_str)
				return (error_handler("malloc error"), free(post_str), free(temp_str), NULL);
			replaced_str = replace_special_parameter(pre_str, data);
			return (free(temp_str), free(post_str), replaced_str);
		}
		i++;
	}
	return (str);
}