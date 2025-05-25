/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuknapek <zuknapek@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:46:37 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/05/04 15:54:38 by zuknapek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h> //sigaction
#include "../libft/libft.h"

extern sig_atomic_t	g_sigstate;

void	handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf("\nIntercepted SIGINT!\n");
		g_sigstate = SIGINT;
	}
	if (signal == SIGQUIT)
		g_sigstate = SIGQUIT;
}

// more signals are to be introduced later
void	sig_init(void)
{
	struct sigaction	sa;
	// sigset_t			block_mask[2];
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = handle_signal;
	// sa.sa_flags = SA_RESTART;
	// sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
