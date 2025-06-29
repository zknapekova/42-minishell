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

int	execute(t_data *data, t_ast *node, char **argv)
{
	char	**env;
	int		status;

//	ft_printf("%s pipe input: %d pipe output: %d\n", argv[0], node->cmd_data->fd_pipe_out, node->cmd_data->fd_pipe_in);
	if (!ft_redirect(node))
		return EXIT_FAILURE;
	close_pipes(data, data->ast);
	if (check_built_ins(argv[0]))
	{
		execute_built_cmds(argv, data, &status);
		return (status);
	}
	else
	{
		node->cmd_data->cmd_path = get_cmd_path(argv[0], data, &status);
		if (!node->cmd_data->cmd_path)
			return (status);
		env = create_env_arr(data);
		if (execve(node->cmd_data->cmd_path, argv, env) == -1)
			return (error_handler(strerror(errno)), free_argv(argv), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}


int	process_cmds_redirs(t_data *data, t_ast *node)
{
	char		**argv;
	t_redir		*redir;
	int			pid;
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
			execute_built_cmds(argv, data, &status);
			if (!ft_strcmp(argv[0], "exit"))
				exit(status); //TODO: add free memory
			return (status);
		}
		pid = fork();
		if (pid < 0)
		{
			error_handler(strerror(errno));
			status = EXIT_FAILURE;
			return (status); //TODO CHECK if it shouldn't return pid
		}
		if (pid == 0)
		{
			status = execute(data, node, argv);
			exit(status);
		}
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			if (ft_strcmp(argv[0], "exit") == 0)
				exit(WEXITSTATUS(status)); //TODO add memory release
			return (WEXITSTATUS(status));
		}
		free_argv(argv);
	}
	return (status);
}

void	find_cmds(t_data *data, t_ast *node)
{
	static int status;

	if (!node)
		return ;
	if (node->type == NODE_OR)
	{
		find_cmds(data, node->left);
		update_last_status(data, status);
		if (status == EXIT_SUCCESS)
			return ;
		find_cmds(data, node->right);
		update_last_status(data, status);
		return ;
	}
	if (node->type == NODE_PIPE)
	{
		if (!open_pipe(node))
				return ;
	}
	if (node->type == NODE_COMMAND && node->cmd_data)
	{
		status = process_cmds_redirs(data, node);
//		ft_printf("status: %d\n", status);
//		ft_printf("fd_pipe_in: %d fd_pipe_out: %d\n", node->cmd_data->fd_pipe_in, node->cmd_data->fd_pipe_out);
		if (node->cmd_data->fd_pipe_in > 1)
			close(node->cmd_data->fd_pipe_in);
		if (node->cmd_data->fd_pipe_out > 1)
			close(node->cmd_data->fd_pipe_out);
		if (node->cmd_data->fd_file_in > 1)
			close(node->cmd_data->fd_file_in);
		if (node->cmd_data->fd_file_out > 1)
			close(node->cmd_data->fd_file_out);
		update_last_status(data, status);
		if (status != EXIT_SUCCESS)
			return ;
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