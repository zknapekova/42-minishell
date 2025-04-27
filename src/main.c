/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:13:59 by zuknapek          #+#    #+#             */
/*   Updated: 2025/04/13 19:37:51 by zuknapek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../include/minishell.h"
#include "../libft/libft.h"
#include <signal.h> // for the SIG type macro
#include <stdlib.h>
#include <errno.h>
#include <string.h>


volatile sig_atomic_t	g_sigstate;

/*static void	loop(void)
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
}*/

#include <stdio.h>
int	main(int argc, char **argv, char **env)
{
    t_data	*data;

	char	str[50] = "my_var3$USER$USER=$USER";
	if (argc != 1)
        return(error_handler("No arguments are accepted"), EXIT_FAILURE);
    (void)argv;
	data = init_data();
	if (!data)
		return(EXIT_FAILURE);
    if (!init_env(env, data))
	{
        return(free_all(data), EXIT_FAILURE);
	}
	if (!handle_new_env_value(data, str))
	    return(free_all(data), EXIT_FAILURE);
	t_env_node *extend_env_node = search_env_list(data, "my_var3zknapeko");
	printf("%s\n", extend_env_node->key_value);
    //sig_init();
	//loop();
	free_all(data);
	return (EXIT_SUCCESS);
}