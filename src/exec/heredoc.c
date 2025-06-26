/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:18:38 by zuknapek          #+#    #+#             */
/*   Updated: 2025/06/26 18:38:02 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"
#include "env_vars.h"
#include "exec.h"
#include <stdlib.h> //for NULL
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h> // for readline
#include <readline/readline.h>

extern sig_atomic_t	g_sigstate;


int	ft_get_file_cont(char *lim, int fd)
{
	char	*line;
	char	*limiter;
	char	*line2;

	line = NULL;
	limiter = ft_strjoin(lim, "\n");
	if (!limiter)
		return (error_handler("malloc failed"), free(lim), close(fd), 0);
	while (1)
	{
		line = readline("> ");
		if (g_sigstate)
			return (free(line), free(limiter), close(fd), 0);
		if (!line)
		{
			ft_eprintf("bash: warning: here-document delimited by end-of-file (wanted `%s')\n", lim);
			break ;
		}
		line2 = ft_strjoin(line, "\n");
		if (!ft_strcmp(limiter, line2))
			break ;
		if (write(fd, line2, ft_strlen(line2)) == -1)
			return (free(line), free(line2), free(limiter), close(fd), 0);
		free(line);
	}
	return (free(line), free(lim), free(limiter), close(fd), 1);
}

int	execute_heredoc(t_redir *redir, t_data *data, t_ast *node)
{
	char	*limiter;
	int		pid;
	int		pipe_fd[2];
	int		status;

	g_sigstate = 0;
	ignore_int_quit();
	limiter = get_redir_target_str(data, redir->target);
	if (!limiter)
		return (error_handler("No limit word"), -1);
	if (pipe(pipe_fd) == -1)
		return (error_handler(strerror(errno)), free(limiter), -1);
	pid = fork();
	if (pid < 0)
		return (free(limiter), close(pipe_fd[1]), close(pipe_fd[0]), -1);
	else if (pid == 0)
	{
		sig_init_heredoc();
		if (!ft_get_file_cont(limiter, pipe_fd[1]))

			exit(EXIT_FAILURE);
	
			
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &status, 0);
	sig_init();
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 0)
			node->cmd_data->fd_pipe_out = pipe_fd[0];

		else
			close(pipe_fd[0]);
		return (free(limiter), close(pipe_fd[1]), WEXITSTATUS(status));
	}
	return (free(limiter), close(pipe_fd[1]), close(pipe_fd[0]), EXIT_FAILURE);
}

int	handle_status(int status)
{
	if (WIFSIGNALED(status))
		status = 128 + WTERMSIG(status);
	else if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}
