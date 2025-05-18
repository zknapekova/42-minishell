/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuknapek <zuknapek@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:13:59 by zuknapek          #+#    #+#             */
/*   Updated: 2025/05/11 19:51:57 by zuknapek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../include/minishell.h"
#include "../libft/libft.h"
#include <signal.h> // for the SIG type macro
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

volatile sig_atomic_t	g_sigstate;

static void	loop(void)
{
	while (g_sigstate != SIGQUIT)
	{
		// read input
		// save it to the history
		// parse input
		// fork
		// run command
		continue ;
	}
	ft_printf("The end\n");
}

int	cd(char **input, t_data *data);

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
	loop();
	free_all(data);
	return (EXIT_SUCCESS);
}
