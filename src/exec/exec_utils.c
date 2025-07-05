#include "exec.h"
#include "env_vars.h"
#include "main.h"
#include "parser_utils.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int	execute(t_data *data, t_ast *node, char **argv)
{
	char	**env;
	int		status;

	if (!ft_redirect(node))
		return EXIT_FAILURE;
	close_pipes(data, data->ast);
	if (check_built_ins(argv[0]))
	{
		execute_built_cmds(argv, data, &status, node);
		return (status);
	}
	else
	{
		node->cmd_data->cmd_path = get_cmd_path(argv[0], data, &status);
		if (!node->cmd_data->cmd_path)
			return (status);
		env = create_env_arr(data);
		if (execve(node->cmd_data->cmd_path, argv, env) == -1)
			return (error_handler(strerror(errno)), free_argv(argv), free_all(data, 1), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	process_cmds_redirs(t_data *data, t_ast *node)
{
	char		**argv;
	t_redir		*redir;
	int 		status;

	status = EXIT_SUCCESS;
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
			execute_built_cmds(argv, data, &status, node);
			if (!ft_strcmp(argv[0], "exit"))
			{
				free_argv(argv);
				free_all(data, 1);
				exit(status);
			}
			free_argv(argv);
			return (status);
		}
		execute_child_process(data, node, &status, argv);
		if (ft_strcmp(argv[0], "exit") == 0)
		{
			free_argv(argv);
			free_all(data, 1);
			exit(status);
		}
		free_argv(argv);
		return (status);
	}
	return (status);
}

void	find_cmds(t_data *data, t_ast *node, int *status)
{
	static int status_stat;

	*status = status_stat;
	if (!node)
		return ;
	if (node->type == NODE_OR)
	{
		find_cmds(data, node->left, &status_stat);
		update_last_status(data, status_stat);
//		ft_printf("5status: %d\n", status_stat);
		wait_all_cmds(data, data->ast, &status_stat);
//		ft_printf("6status: %d\n", status_stat);
		*status = status_stat;
		if (status_stat == EXIT_SUCCESS)
			return ;
		find_cmds(data, node->right, &status_stat);
		update_last_status(data, status_stat);
		*status = status_stat;
		return ;
	}
	if (node->type == NODE_AND)
	{
		find_cmds(data, node->left, &status_stat);
		update_last_status(data, status_stat);
		wait_all_cmds(data, data->ast, &status_stat);
		*status = status_stat;
		if (status_stat != EXIT_SUCCESS)
			return ;
		find_cmds(data, node->right, &status_stat);
		update_last_status(data, status_stat);
		wait_all_cmds(data, data->ast, &status_stat);
		*status = status_stat;
		return ;
	}
	if (node->type == NODE_PIPE)
	{
		if (!open_pipe(node))
				return ;
	}
	if (node->type == NODE_COMMAND && node->cmd_data)
	{
		status_stat = process_cmds_redirs(data, node);
		node->cmd_data->status = status_stat;
		if (node->cmd_data->fd_pipe_in > 1)
			close(node->cmd_data->fd_pipe_in);
		if (node->cmd_data->fd_pipe_out > 1)
			close(node->cmd_data->fd_pipe_out);
		if (node->cmd_data->fd_file_in > 1)
			close(node->cmd_data->fd_file_in);
		if (node->cmd_data->fd_file_out > 1)
			close(node->cmd_data->fd_file_out);
		update_last_status(data, status_stat);
		*status = status_stat;
		if (status_stat != EXIT_SUCCESS)
			return ;
	}
	find_cmds(data, node->left, &status_stat);
	find_cmds(data, node->right, &status_stat);
}

void	handle_cmds(t_data *data, t_ast *node)
{
	int		backup_stdin;
	int		backup_stdout;
	int		status;

	set_heredoc_flag(data->ast);
	status = EXIT_SUCCESS;
	sig_ignore_int_quit();
	backup_stdin = dup(STDIN_FILENO);
	backup_stdout = dup(STDOUT_FILENO);
	find_cmds(data, node, &status);
	update_last_status(data, status);
	dup2(backup_stdin, STDIN_FILENO);
	dup2(backup_stdout, STDOUT_FILENO);
	close_pipes(data, data->ast);
	wait_all_cmds(data, data->ast, &status);
	print_nl_after_sig(status);
	sig_init();
}
