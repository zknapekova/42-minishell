/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 19:13:59 by zuknapek          #+#    #+#             */
/*   Updated: 2025/06/30 23:36:27 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../libft/libft.h"
#include "../include/env_vars.h"
#include <stdlib.h>
#include <errno.h>
#include <string.h>

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (error_handler(strerror(errno)), NULL);
	data->head = NULL;
	data->tokens = NULL;
	data->ast = NULL;
	return (data);
}

int	init_env(char **env, t_data *data)
{
	t_env_node	*node;
	t_env_node	*last;
	char		*env_cp;

	env_cp = ft_strdup(*env);
	node = new_node(data, env_cp);
	if (!node)
		return (0);
	env++;
	while (*env)
	{
		env_cp = ft_strdup(*env);
		node = new_node(data, env_cp);
		if (!node)
			return (0);
		last = last_node(data);
		last->next = node;
		env++;
	}
	if (!add_env(data, ft_strdup("?=0")))
		return (0);
	return (1);
}
