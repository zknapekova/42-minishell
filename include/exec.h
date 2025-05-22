#ifndef EXEC_H
# define EXEC_H

#include "main.h"
char	**get_argv(t_data *data, t_arg *args);
char	*get_arg_str(t_data *data, t_arg **args);
void	print_ast_argv(t_data *data, t_ast *node, int depth);
int	get_list_len(t_arg *args);
void	free_argv(char **argv);
char	*get_redir_target_str(t_data *data, t_redir_target *target);

#endif