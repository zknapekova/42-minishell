/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuknapek <zuknapek@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:13:59 by zuknapek          #+#    #+#             */
/*   Updated: 2025/04/10 21:04:26 by zuknapek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

static t_data	*init_data() //tuto funkciu mozeme pouzit na inicializaciu premennych pre cely minishell
{
	t_data	*data;
	
	data = malloc(sizeof(t_data));
	if (!data)
		return (error_handler(strerror(errno)), NULL);
	data->head = NULL;
	return(data);
}

int	main(int argc, char **argv, char **env)
{
    t_data	*data;
	
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
	free_all(data);
	return (EXIT_SUCCESS);
}