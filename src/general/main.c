/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:13:59 by zuknapek          #+#    #+#             */
/*   Updated: 2025/05/21 16:58:16 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"
#include "token.h"
#include "parser_utils.h"
#include "exec.h" // fot the get_arg_list()
#include <signal.h> // for the SIG type macro
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h> // for readline
#include <readline/readline.h>
#include <readline/history.h>

volatile sig_atomic_t	g_sigstate;

static void	loop(t_data *data)
{
	char	*line;
	t_token	*temp_token_list;

	while (g_sigstate != SIGQUIT && g_sigstate != SIGINT)
	{
		// ***read input
		line = readline("minishell> ");
		if (!line)
			break ;
		data->tokens = lexer(line);
		free(line);
		temp_token_list = data->tokens;
		// print_tokens(data->tokens);
		data->ast = parser(&temp_token_list);
		// print_ast(data->ast, 0);
		print_ast_argv(data, data->ast, 0);
		free_token_list(&(data->tokens));
		data->tokens = NULL;
		free_ast(data->ast);
	}
	ft_printf("The end\n");
}

int	cd(char **input, t_data *data);

#include "env_vars.h"

int	main(int argc, char **argv, char **env)
{
	t_data	*data;

	if (argc != 1)
		return (error_handler("No arguments are accepted"), EXIT_FAILURE);
	(void)argv;
	data = init_data();
	if (!data)
		return (EXIT_FAILURE);
	if (!init_env(env, data))
		return (free_all(data), EXIT_FAILURE);
	sig_init();
	
	// char *extend_val;

	// extend_val = extend_env_value_nf(data, "asdf$abc");
	// // ft_printf("HOME %s\n", echo_extend_env_value(data, "HOME"));
	// ft_printf("$HOME %s\n", extend_val);
	// free (extend_val);
	
	loop(data);
	char	*test[2];
	test[0]="~/Documents";
	test[1]=NULL;
	printf("status: %d\n", cd(test, data));
	free_all(data);
	return (EXIT_SUCCESS);
}
