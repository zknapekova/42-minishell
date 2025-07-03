#include "exec.h"
#include "env_vars.h"
#include "main.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <stdio.h> // for readline
#include <readline/readline.h>
#include <readline/history.h>

int	update_last_status(t_data *data, int status)
{
	t_env_node	*node;
	char		*temp;

	node = search_env_list(data, "?");
	free(node->value);
	node->value = NULL;
	node->value = ft_itoa(status);
	if (!node->value)
		return (error_handler("malloc error: updating $? failed"), 0);
	free(node->key_value);
	node->key_value = NULL;
	temp = ft_strjoin(node->key, "=");
	if (!temp)
		return (error_handler("malloc error: updating $? failed"), 0);
	node->key_value = ft_strjoin(temp, node->value);
	free(temp);
	if (!node->key_value)
		return (error_handler("malloc error: updating $? failed"), 0);
	return (1);
}

void	wait_all_cmds(t_data *data, t_ast *node, int *status)
{
	int	status1;

	if (!node)
		return ;
	status1 = 0;
	if (node->type == NODE_COMMAND)
	{
		if (node->cmd_data->pid == -1)
			return ;
		else
		{
			waitpid(node->cmd_data->pid, &status1, 0);
			if (WIFEXITED(status1))
			{
				*status = WEXITSTATUS(status1);
				update_last_status(data, WEXITSTATUS(status1));
			}
			else if (WIFSIGNALED(status1))
			{
				*status = WTERMSIG(status1);
				update_last_status(data, 128 + WTERMSIG(status1));
			}
		}
	}
	wait_all_cmds(data, node->left, status);
	wait_all_cmds(data, node->right, status);
}

void	execute_child_process(t_data *data, t_ast *node, int *status, char **argv)
{
	node->cmd_data->pid = fork();
	if (node->cmd_data->pid < 0)
	{
		error_handler(strerror(errno));
		*status = EXIT_FAILURE; //TODO CHECK if it shouldn't return pid
	}
	if (node->cmd_data->pid == 0)
	{
		rl_clear_history();
		default_int_quit();
		*status = execute(data, node, argv);
		free_argv(argv);
		free_all(data, 1);
		exit(*status);
	}
}