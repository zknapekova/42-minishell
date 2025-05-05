/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:13:59 by zuknapek          #+#    #+#             */
/*   Updated: 2025/05/05 19:37:49 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../libft/libft.h"
#include "../include/token.h"
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
	// t_token	*tokens;

	while (g_sigstate != SIGQUIT && g_sigstate != SIGINT)
	{
		// read input
		line = readline("minishell> ");
		data->tokens = lexer(line);
		print_tokens(data->tokens);
		data->ast = parser(&(data->tokens));
		// if (!data->ast)
		// {
		// 	error_handler("Parser failed :'(");
		// 	break;
		// }
			
		free_token_list(data->tokens);
		data->tokens = NULL;
		free(line);
		free_ast(data->ast);
		continue ;
	}
	ft_printf("Bye!\n");
}

static t_data	*init_data() //tuto funkciu mozeme pouzit na inicializaciu premennych pre cely minishell
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (error_handler(strerror(errno)), NULL);
	data->head = NULL;
	data->tokens = NULL;
	data->ast = NULL;
	return (data);
}

#include <stdio.h>
int	main(int argc, char **argv, char **env)
{
    t_data	*data;
	char	str[50] = "USER33=$USERjgrigor";
	
	if (argc != 1)
        return(error_handler("No arguments are accepted"), EXIT_FAILURE);
    (void)argv;
	data = init_data();
	if (!data)
		return(EXIT_FAILURE);
    if (!init_env(env, data))
	{
        return(free_all(data), EXIT_FAILURE);
	}
	
	replace_env_value(data, str);
  sig_init();
	loop(data);
	free_all(data);
	return (EXIT_SUCCESS);
}