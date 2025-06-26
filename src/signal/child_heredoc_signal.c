/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_heredoc_signal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:58:29 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/26 19:01:11 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <readline/readline.h>
#include <signal.h> //sigaction
#include <stdio.h>  // for readline

extern sig_atomic_t	g_sigstate;

void	handle_heredoc_signal(int signum)
{
	if (signum == SIGINT)
	{
		g_sigstate = 1;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		write(1, "\n", 1);
		exit (130);
	}
	
}

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

void sig_init_heredoc(void)
{
	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = handle_heredoc_signal;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	ignore_int_quit(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	default_int_quit(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}