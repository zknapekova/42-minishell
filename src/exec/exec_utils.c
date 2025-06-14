#include "exec.h"
#include "env_vars.h"
#include "main.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int	process_cmds_redirs(t_data *data, t_ast *node, int pid)
{
	char	**argv;
	t_redir	*redir;
	char	**env;

	(void)pid;
	if (node->cmd_data->redirs)
	{
		redir = node->cmd_data->redirs;
		handle_redir_files(redir, data);
	}
	if (node->cmd_data->args)
	{
		argv = get_argv(data, node->cmd_data->args);
		if (!argv)
			return (0);
		if (!ft_redirect(node->cmd_data->fd_pipe_out, node->cmd_data->fd_pipe_in))
			return (0);
		close_pipes(data, data->ast);
		if (check_built_ins(argv[0]))
		{
			if (!execute_built_cmds(argv, data))
				return (0);
		}
		else
		{
			node->cmd_data->cmd_path = get_cmd_path(argv[0], data);
			if (!node->cmd_data->cmd_path)
				return (0);
			env = create_env_arr(data);
			if (execve(node->cmd_data->cmd_path, argv, env) == -1)
				return (strerror(errno), free_argv(argv), 0);
		}
	}
	free_argv(argv);
	return (1);
}

void	find_cmds(t_data *data, t_ast *node)
{
	int	pid;

	if (!node)
		return ;
	if (node->type == NODE_PIPE)
	{
		if (!open_pipe(node))
				return ;
	}
	if (node->type == NODE_COMMAND && node->cmd_data)
	{
		pid = fork();
		if (pid < 0)
		{
			error_handler(strerror(errno));
			return ;
		}
		if (pid == 0)
		{
			if (!process_cmds_redirs(data, node, pid))
				exit(EXIT_FAILURE);
			exit(EXIT_SUCCESS);
		}
		waitpid(pid, NULL, 0);
		if (node->cmd_data->fd_pipe_in > 1)
			close(node->cmd_data->fd_pipe_in);
	}
	find_cmds(data, node->left);
	find_cmds(data, node->right);
}


void	handle_cmds(t_data *data, t_ast *node)
{
	int		backup_stdin;
	int		backup_stdout;

	backup_stdin = dup(STDIN_FILENO);
	backup_stdout = dup(STDOUT_FILENO);
	find_cmds(data, node);
	dup2(backup_stdin, STDIN_FILENO);
	dup2(backup_stdout, STDOUT_FILENO);
	close_pipes(data, data->ast);
}