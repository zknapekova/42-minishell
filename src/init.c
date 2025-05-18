/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuknapek <zuknapek@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:49:34 by zuknapek          #+#    #+#             */
/*   Updated: 2025/05/04 15:52:48 by zuknapek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../libft/libft.h"
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
	return (1);
}
