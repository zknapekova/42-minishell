#include "env_vars.h"
#include "exec.h"
#include "libft.h"
#include "main.h"
#include "parser_utils.h" // for print_indent()
#include <errno.h>
#include <stdlib.h> //for NULL
#include <string.h>
#include <sys/wait.h>

void	get_input_output_fd(int *input_fd, int *output_fd, t_ast *node)
{
	*input_fd = -1;
	*output_fd = -1;
	if (node->cmd_data->fd_file_in != -1)
		*input_fd = node->cmd_data->fd_file_in;
	else if (node->cmd_data->fd_pipe_out != -1)
		*input_fd = node->cmd_data->fd_pipe_out;
	if (node->cmd_data->fd_file_out != -1)
		*output_fd = node->cmd_data->fd_file_out;
	else if (node->cmd_data->fd_pipe_in != -1)
		*output_fd = node->cmd_data->fd_pipe_in;
}


int	input_output_redirect(t_data *data, t_redir *redir, t_ast *node)
{
	char	*redir_file_path;
	char	*updated_path;

	redir_file_path = get_redir_target_str(data, redir->target);
	if (!redir_file_path)
		return (EXIT_FAILURE);
	updated_path = handle_path(redir_file_path, 1, 0, 0);
	if (!updated_path)
		return (EXIT_FAILURE);
	if (redir->type == REDIR_INPUT)
	{
		node->cmd_data->fd_file_in = get_fd_file(updated_path,
				redir->type);
		if (node->cmd_data->fd_file_in == -1)
			return (free(updated_path), EXIT_FAILURE);
	}
	if (redir->type == REDIR_OUTPUT || redir->type == REDIR_APPEND)
	{
		node->cmd_data->fd_file_out = get_fd_file(updated_path,
				redir->type);
		if (node->cmd_data->fd_file_out == -1)
			return (free(updated_path), EXIT_FAILURE);
	}
	return (free(updated_path), EXIT_SUCCESS);
}