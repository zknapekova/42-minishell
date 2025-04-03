/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:46:37 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/04/03 17:34:38 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h> //sigaction
#include "../libft/libft.h"

extern int g_sigstate;

void	handle_signal(int signal)
{
	if (signal == SIGINT)
		ft_printf("\nIntercepted SIGINT!\n");
	if (signal == SIGQUIT)
		g_sigstate = SIGQUIT;
}

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