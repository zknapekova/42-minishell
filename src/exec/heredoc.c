#include "main.h"
#include "libft.h"
#include "env_vars.h"
#include "exec.h"
#include "parser_utils.h" // for print_indent()
#include <stdlib.h> //for NULL
#include <stdio.h> // for readline
#include <readline/readline.h>

void	setup_heredoc(char *target)
{
	int		pipefd[2];
	char	*line;

	line = NULL;
	if (pipe(pipefd) == -1)
		error_handler("pipe");
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, target, ft_strlen(target)) == 0)
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]); // Finished writing
	dup2(pipefd[0], 0); // Redirect stdin to read from pipe
	close(pipefd[0]);
}
