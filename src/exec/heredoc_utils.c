/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 01:57:37 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/07/09 01:58:19 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_vars.h"
#include "exec.h"
#include "libft.h"
#include "main.h"
#include <errno.h>
#include <stdio.h>  // for readline
#include <stdlib.h> //for NULL
#include <string.h>

void	heredoc_signal_handler(char *limiter, char *lim, t_data *data)
{
	free(limiter);
	free(lim);
	free_all(data, 1);
	exit(130);
}

void	heredoc_write_line(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	free(line);
}

void	print_heredoc_error(char *lim)
{
	ft_eprintf("minishell: warning: here-document delimited \
by end-of-file (wanted `%s')\n", lim);
}

char	*expand_line(char *line, t_data *data)
{
	char	*expanded;

	if (get_first_ind(line, '$', 0) != -1)
		expanded = extend_env_value_nf(data, line);
	else
		expanded = ft_strdup(line);
	free(line);
	return (expanded);
}

char	*get_line(char *line, char *limiter, t_data *data)
{
	line = ft_strjoin_ed(line, "\n", 1);
	line = expand_line(line, data);
	if (!ft_strcmp(limiter, line))
	{
		free(line);
		line = NULL;
	}
	return (line);
}
