/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_ops.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuknapek <zuknapek@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 19:47:56 by zuknapek          #+#    #+#             */
/*   Updated: 2025/04/10 21:21:49 by zuknapek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "stdlib.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>

static int	lst_size(t_data *data)
{
	t_env_node	*temp;
	int			len;

	len = 0;
	if (!data->head)
		return (0);
	temp = data->head;
	while (temp)
	{
		temp = temp->next;
		len++;
	}
	free(temp);
	return (len);
}

static t_env_node	*new_node(t_data *data, char *key_value)
{
	t_env_node *new_node;


    new_node = malloc(sizeof(t_env_node));
    if (!new_node)
	{
        return (error_handler(strerror(errno)), NULL);
	}
	new_node->key_value = key_value;
	new_node->next = NULL;
	if (lst_size(data) == 0)
		data->head = new_node;
	return(new_node);
}

static t_env_node	*last_node(t_data *data)
{
	t_env_node	*temp;

	temp = data->head;
	while (temp && temp->next)
		temp = temp->next;
	return(temp);
}

int init_env(char **env, t_data *data)
{
    t_env_node *node;
	t_env_node *last;

	node = new_node(data, *env);
	while (*env)
	{
        node = new_node(data, *env);
        last = last_node(data);
        last->next = node;
        env++;
	}
    return (1);
}