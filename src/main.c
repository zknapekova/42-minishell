/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:13:59 by zuknapek          #+#    #+#             */
/*   Updated: 2025/04/04 16:11:39 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../include/minishell.h"
#include "../libft/libft.h"
#include <signal.h> // for the SIG type macro

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



int	main(void)
{
	sig_init();
	loop();
	return (0);
}