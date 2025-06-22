#include "main.h"
#include "libft.h"
#include "env_vars.h"
#include "exec.h"
#include "parser_utils.h" // for print_indent()
#include <stdlib.h> //for NULL
#include <stdio.h> // for readline
#include <readline/readline.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>


int	ft_get_file_cont(char *lim, int fd)
{
	char	*line;
	char	*limiter;

	line = NULL;
	limiter = ft_strjoin(lim, "\n");
	if (!limiter)
		return (error_handler("malloc failed"), free(lim), 0);
	free(lim);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (!ft_strcmp(limiter, line))
			break ;
		if (write(fd, line, ft_strlen(line)) == -1)
			return (free(line), free(limiter), 0);;
		free(line);
	}
	free(line);
	free(limiter);
	return (1);
}

int	execute_heredoc(t_redir *redir, t_data *data, t_ast *node)
{
	char	*limiter;
	int		pid;
	int		pipe_fd[2];
	int		status;

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
		if (!ft_get_file_cont(limiter, pipe_fd[1]))
			exit(EXIT_FAILURE);
		close(pipe_fd[1]);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &status, 0);
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
