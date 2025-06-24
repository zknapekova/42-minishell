/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_signal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:58:29 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/24 21:06:14 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <readline/readline.h>
#include <signal.h> //sigaction
#include <stdio.h>  // for readline

void	sig_init_child(void)
{
	struct sigaction act;

	ft_bzero(&act, sizeof(act));
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
	act.sa_handler = SIG_DFL;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

// void	set_default_signals(void)
// {
// 	struct sigaction sa;
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = 0;
// 	sa.sa_handler = SIG_DFL;
// 	sigaction(SIGINT, &sa, NULL);
// 	sigaction(SIGQUIT, &sa, NULL);
// }