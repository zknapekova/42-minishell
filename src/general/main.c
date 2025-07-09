/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:13:59 by zuknapek          #+#    #+#             */
/*   Updated: 2025/07/09 17:54:42 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"
#include "token.h"
#include "parser_utils.h"
#include "env_vars.h"
#include "exec.h" // fot the get_arg_list()
#include <signal.h> // for the SIG type macro
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h> // for readline
#include <readline/readline.h>
#include <readline/history.h>

static void	loop(t_data *data)
{
	char	*line;
	t_token	*temp_token_list;

	while (1)
	{
		line = readline("\001\033[1;34m\002minishell>\001\033[0m\002 ");
		if (!line)
			break ;
		if (*line != '\0')
		{
			add_history(line);
			data->tokens = lexer(line);
			free(line);
			if (!data->tokens)
			{
				update_last_status(data, 2);
				continue ;
			}
			temp_token_list = data->tokens;
			data->ast = parser(&temp_token_list);
			free_token_list(&(data->tokens));
			if (!data->ast || check_subshell_redirs(data->ast))
			{
				update_last_status(data, 2);
				if (data->ast)
					free_ast(data->ast);
				continue ;
			}
			handle_cmds(data, data->ast);
			free_ast(data->ast);
		}
	}
	ft_printf("exit\n");
}

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
		return (free_all(data, 0), EXIT_FAILURE);
	sig_init();
	loop(data);
	free_all(data, 0);
	return (EXIT_SUCCESS);
}
