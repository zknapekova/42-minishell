/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sig_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 18:22:27 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/28 19:21:06 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_vars.h"
#include "exec.h"
#include "libft.h"
#include "main.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

void	print_nl_after_sig(int status)
{
	int	sig;

	if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			write(1, "\n", 1);
		else if (sig == SIGQUIT)
			write(1, "Quit \n", 6);
	}
}
