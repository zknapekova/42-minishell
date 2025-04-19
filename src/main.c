/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:13:59 by zuknapek          #+#    #+#             */
/*   Updated: 2025/04/18 23:38:34 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../libft/libft.h"
#include <signal.h> // for the SIG type macro
#include <stdlib.h>
#include <errno.h>
#include <string.h>

volatile sig_atomic_t	g_sigstate;

static void	loop(void)
{
	t_token	*token;
	
	token = lexer("   < echo \"hello world\"  'sdaf asdf' && ls -l > out.txt");
	while (token)
	{
		printf("Type: %d, Value: %s\n", token->type, token->value ? token->value : "NULL");
		token = token->next;
	}
	while (g_sigstate != SIGQUIT)
	{
		// read input
		// save it to the history
		// parse input
		// t_token *token;

		// token = lexer("echo \"hello world\"  'sdaf asdf' && ls -l > out.txt");
		// while (token)
		// {
		// 	printf("Type: %d, Value: %s\n", token->type, token->value ? token->value : "NULL");
		// 	token = token->next;
		// }

		// fork
		// run command
		continue ;
	}
	ft_printf("The end\n");
	ft_eprintf("Test error message\n");
}

static t_data	*init_data() //tuto funkciu mozeme pouzit na inicializaciu premennych pre cely minishell
{

	t_data	*data;
	
	data = malloc(sizeof(t_data));
	if (!data)
		return (error_handler(strerror(errno)), NULL);
	data->head = NULL;
	return(data);
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
	loop();
	free_all(data);
	return (EXIT_SUCCESS);
}