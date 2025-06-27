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

//	ft_printf("%s pipe input: %d pipe output: %d\n", argv[0], node->cmd_data->fd_pipe_out, node->cmd_data->fd_pipe_in);
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
	int status;
	int status2;

	if (node->cmd_data->redirs)
	{
		redir = node->cmd_data->redirs;
		status = handle_redir_files(redir, data, node);
		if (status != 0)
			return (status);
	}
	if (node->cmd_data->args)
	{
		argv = get_argv(data, node->cmd_data->args);
		if (!argv)
			return (EXIT_FAILURE);
		if (check_built_ins(argv[0]) && node->cmd_data->fd_pipe_in == -1 && node->cmd_data->fd_pipe_out == -1)
		{
			if (!execute_built_cmds(argv, data))
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		pid = fork();
		if (pid < 0)
		{
			error_handler(strerror(errno));
			return (EXIT_FAILURE); //TODO CHECK if it shouldn't return pid
		}
		if (pid == 0)
		{
			default_int_quit();
			if (!execute(data, node, argv))
				exit(EXIT_FAILURE);
			exit(EXIT_SUCCESS);
		}
		waitpid(pid, &status2, 0);
		print_nl_after_sig(status2);
		// if (WIFSIGNALED(status2))
		// {
		// 	int sig = WTERMSIG(status2);
		// 	if (sig == SIGINT)
		// 		write(1, "\n", 1);
		// 	else if (sig == SIGQUIT)
		// 		write(1, "Quit: 3\n", 8); // Mimic Bash behavior
		// }
		free_argv(argv);
	}
	return (EXIT_SUCCESS);
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
		if (process_cmds_redirs(data, node) != 0)
			return ;
//		ft_printf("fd_pipe_in: %d fd_pipe_out: %d\n", node->cmd_data->fd_pipe_in, node->cmd_data->fd_pipe_out);
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

	sig_ignore_int_quit();
	backup_stdin = dup(STDIN_FILENO);
	backup_stdout = dup(STDOUT_FILENO);
	find_cmds(data, node);
	dup2(backup_stdin, STDIN_FILENO);
	dup2(backup_stdout, STDOUT_FILENO);
	sig_init();
	close_pipes(data, data->ast);
}