/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:18:38 by zuknapek          #+#    #+#             */
/*   Updated: 2025/07/01 23:38:33 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_vars.h"
#include "exec.h"
#include "libft.h"
#include "main.h"
#include <errno.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>  // for readline
#include <stdlib.h> //for NULL
#include <string.h>
#include <sys/wait.h>

extern int	g_heredoc_sig;

int	ft_get_file_cont(char *lim, int fd, t_data *data)
{
	char	*line;
	char	*limiter;

	line = NULL;
	limiter = ft_strjoin(lim, "\n");
	if (!limiter)
		return (error_handler("malloc failed"), free(lim), close(fd), 0);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			if (g_heredoc_sig == 1)
				heredoc_signal_handler(limiter, lim, data);
			print_heredoc_error(lim);
			break ;
		}
		line = get_line(line, limiter, data);
		if (!line)
			break ;
		heredoc_write_line(fd, line);
	}
	return (free(lim), free(limiter), close(fd), 1);
}

int	handle_status(int pid, t_ast *node, int pipe_fd[2])
{
	int		status;

	waitpid(pid, &status, 0);
	sig_init();
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 0)
			node->cmd_data->fd_pipe_out = pipe_fd[0];
		else
			close(pipe_fd[0]);
		return (close(pipe_fd[1]), WEXITSTATUS(status));
	}
	if (WIFSIGNALED(status))
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (128 + WTERMSIG(status));
	}
	return (close(pipe_fd[1]), close(pipe_fd[0]), EXIT_FAILURE);
}

void	execute_heredoc_child(char *limiter, int pipe_fd, t_data *data)
{
	if (!ft_get_file_cont(limiter, pipe_fd, data))
	{
		free_all(data, 1);
		exit(EXIT_FAILURE);
	}
	free_all(data, 1);
	exit(EXIT_SUCCESS);
}

int	execute_heredoc(t_redir *redir, t_data *data, t_ast *node)
{
	char	*limiter;
	int		pid;
	int		pipe_fd[2];

	sig_ignore_int_quit();
	limiter = get_redir_target_str(data, redir->target);
	if (!limiter)
		return (error_handler("No limit word"), 1);
	if (pipe(pipe_fd) == -1)
		return (error_handler(strerror(errno)), free(limiter), 1);
	pid = fork();
	if (pid < 0)
		return (free(limiter), close(pipe_fd[1]), close(pipe_fd[0]), 1);
	else if (pid == 0)
	{
		rl_clear_history();
		sig_init_heredoc();
		execute_heredoc_child(limiter, pipe_fd[1], data);
	}
	return (free(limiter), handle_status(pid, node, pipe_fd));
}
