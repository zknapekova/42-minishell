/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_ops.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuknapek <zuknapek@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:23:43 by zuknapek          #+#    #+#             */
/*   Updated: 2025/04/12 19:09:27 by zuknapek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../libft/libft.h"
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

t_env_node	*new_node(t_data *data, char *key_value)
{
	t_env_node *new_node;
	char		**split_str;

    new_node = malloc(sizeof(t_env_node));
    if (!new_node)
	{
        return (error_handler(strerror(errno)), NULL);
	}
	new_node->key_value = key_value;
	new_node->next = NULL;
	split_str = ft_split(key_value, '=');
	if (!split_str)
		return (error_handler(strerror(errno)), NULL);
	new_node->key = split_str[0];
	new_node->value = split_str[1];
	if (lst_size(data) == 0)
		data->head = new_node;
	return(new_node);
}

t_env_node	*last_node(t_data *data)
{
	t_env_node	*temp;

	temp = data->head;
	while (temp && temp->next)
		temp = temp->next;
	return(temp);
}
