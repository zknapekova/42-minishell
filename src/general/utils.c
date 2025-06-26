/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:44:37 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/25 18:31:12 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdio.h> // for readline
#include <signal.h> //for sig_atomic_t


extern sig_atomic_t	g_sigstate;

    char	*read_user_input(void)
{
	if (g_sigstate == 1)
	{
		g_sigstate = 0;
		return (readline(""));
	}
	return (readline("minishell> "));
}
int	*get_rl_active(void)
{
	static int	is_active;

	return (&is_active);
}