#include "exec.h"
#include "env_vars.h"
#include "main.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int	update_last_status(t_data *data, int status)
{
	t_env_node	*node;

	node = search_env_list(data, "?");
	node->value = ft_itoa(status);
	if (!node->value)
		return (error_handler("malloc error: updating $? failed"), 0);
	free(node->key_value);
	node->key_value = NULL;
	node->key_value = ft_strjoin(node->key, node->value);
	if (!node->key_value)
		return (error_handler("malloc error: updating $? failed"), 0);
	return (1);
}

void	wait_all_cmds(t_data *data, t_ast *node, int *status)
{
	int	status1;

	if (!node)
		return ;
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
				*status = WEXITSTATUS(status1);
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
		default_int_quit();
		*status = execute(data, node, argv);
		free(argv);
		free_all(data);
		exit(*status);
	}
}