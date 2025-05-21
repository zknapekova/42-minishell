#ifndef EXEC_H
# define EXEC_H

#include "main.h"
char	**get_arg_list(t_data *data, t_arg *args);
void	print_ast_argv(t_data *data, t_ast *node, int depth);

#endif