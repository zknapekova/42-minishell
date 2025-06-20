#include "exec.h"
#include "env_vars.h"
#include "main.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int	execute(t_data *data, t_ast *node, char **argv)
{
	char	**env;

	//ft_printf("%s pipe input: %d pipe output: %d\n", argv[0], node->cmd_data->fd_pipe_out, node->cmd_data->fd_pipe_in);
	if (!ft_redirect(node))
		return (0);
	close_pipes(data, data->ast);
	if (check_built_ins(argv[0]))
	{
		if (!execute_built_cmds(argv, data))
			return (0);
		return (1);
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
	return (1);
}


int	process_cmds_redirs(t_data *data, t_ast *node)
{
	char	**argv;
	t_redir	*redir;
	int		pid;

	if (node->cmd_data->redirs)
	{
		redir = node->cmd_data->redirs;
		handle_redir_files(redir, data, node);
	}
	if (node->cmd_data->args)
	{
		argv = get_argv(data, node->cmd_data->args);
		if (!argv)
			return (0);
		if (check_built_ins(argv[0]) && node->cmd_data->fd_pipe_in == -1 && node->cmd_data->fd_pipe_out == -1)
		{
			if (!execute_built_cmds(argv, data))
				return (0);
			return (1);
		}
		pid = fork();
		if (pid < 0)
		{
			error_handler(strerror(errno));
			return (0);
		}
		if (pid == 0)
		{
			if (!execute(data, node, argv))
				exit(EXIT_FAILURE);
			exit(EXIT_SUCCESS);
		}
		waitpid(pid, NULL, 0);
		free_argv(argv);
	}
	return (1);
}

void	find_cmds(t_data *data, t_ast *node)
{
	if (!node)
		return ;
	if (node->type == NODE_PIPE)
	{
		if (!open_pipe(node))
				return ;
	}
	if (node->type == NODE_COMMAND && node->cmd_data)
	{
		if (!process_cmds_redirs(data, node))
			return ;
		//ft_printf("fd_pipe_in: %d fd_pipe_out: %d\n", node->cmd_data->fd_pipe_in, node->cmd_data->fd_pipe_out);
		if (node->cmd_data->fd_pipe_in > 1)
			close(node->cmd_data->fd_pipe_in);
		if (node->cmd_data->fd_pipe_out > 1)
			close(node->cmd_data->fd_pipe_out);
		if (node->cmd_data->fd_file_in > 1)
			close(node->cmd_data->fd_file_in);
		if (node->cmd_data->fd_file_out > 1)
			close(node->cmd_data->fd_file_out);
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