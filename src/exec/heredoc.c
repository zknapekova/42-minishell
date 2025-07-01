/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:18:38 by zuknapek          #+#    #+#             */
/*   Updated: 2025/07/01 20:23:41 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_vars.h"
#include "exec.h"
#include "libft.h"
#include "main.h"
#include <errno.h>
#include <readline/readline.h>
#include <stdio.h>  // for readline
#include <readline/history.h>
#include <stdlib.h> //for NULL
#include <string.h>
#include <sys/wait.h>


// expands env variables present in heredoc, frees line
char	*expand_line(char *line, t_data *data)
{
	char	*expanded;

	if (get_first_ind(line, '$', 0) != -1)
		expanded = extend_env_value_nf(data, line);
	else
		expanded = ft_strdup(line);
	free(line);
	return (expanded);
}

int	ft_get_file_cont(char *lim, int fd, t_data *data)
{
	char	*line;
	char	*limiter;
	// char	*line2;

	line = NULL;
	limiter = ft_strjoin(lim, "\n");
	if (!limiter)
		return (error_handler("malloc failed"), free(lim), close(fd), 0);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_eprintf("minishell: warning: here-document delimited by end-of-file (wanted `%s')\n",
				lim);
			break ;
		}
		line = ft_strjoin_ed(line, "\n", 1);
		line = expand_line(line, data);
		if (!ft_strcmp(limiter, line))
		{
			free(line);
			break ;
		}
			
		if (write(fd, line, ft_strlen(line)) == -1)
			return (free(line), free(limiter), close(fd), 0);
		free(line);
	}
	return (free(lim), free(limiter), close(fd), 1);
}

int	execute_heredoc(t_redir *redir, t_data *data, t_ast *node)
{
	char	*limiter;
	int		pid;
	int		pipe_fd[2];
	int		status;

	sig_ignore_int_quit();
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
		rl_clear_history();
		sig_init_heredoc();
		if (!ft_get_file_cont(limiter, pipe_fd[1], data))
		{
			free_all(data, 1);
			exit(EXIT_FAILURE);
		}
		free_all(data, 1);
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
	if (WIFSIGNALED(status))
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (free(limiter), 128 + WTERMSIG(status));
	}
	return (free(limiter), close(pipe_fd[1]), close(pipe_fd[0]), EXIT_FAILURE);
}
