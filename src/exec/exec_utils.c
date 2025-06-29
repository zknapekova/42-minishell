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

void	wait_all_cmds(t_data *data, t_ast *node, int status)
{
	if (!node)
		return ;
	if (node->type == NODE_COMMAND)
	{
		if (node->cmd_data->pid == -1)
			return ;
		else
		{
			waitpid(node->cmd_data->pid, &status, 0);
			if (WIFEXITED(status))
				update_last_status(data, WEXITSTATUS(status));
			else if (WIFSIGNALED(status))
				update_last_status(data, 128 + WTERMSIG(status));
		}
	}
	wait_all_cmds(data, node->left, status);
	wait_all_cmds(data, node->right, status);
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
			execute_built_cmds(argv, data, &status);
			if (!ft_strcmp(argv[0], "exit"))
			{
				free_argv(argv);
				exit(status); //TODO: add free memory
			}
			return (status);
		}
		execute_child_process(data, node, &status, argv);
		if (ft_strcmp(argv[0], "exit") == 0)
		{
			free_argv(argv);
			exit(status);//TODO add memory release
		}
		print_nl_after_sig(status);
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
		*status = status_stat;
		if (status_stat == EXIT_SUCCESS)
			return ;
		find_cmds(data, node->right, &status_stat);
		update_last_status(data, status_stat);
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

	status = EXIT_SUCCESS;
	sig_ignore_int_quit();
	backup_stdin = dup(STDIN_FILENO);
	backup_stdout = dup(STDOUT_FILENO);
	find_cmds(data, node, &status);
	update_last_status(data, status);
	dup2(backup_stdin, STDIN_FILENO);
	dup2(backup_stdout, STDOUT_FILENO);
	sig_init();
	close_pipes(data, data->ast);
	wait_all_cmds(data, data->ast, status);
}