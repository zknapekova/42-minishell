/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_ops.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:23:43 by zuknapek          #+#    #+#             */
/*   Updated: 2025/05/18 23:26:04 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_vars.h"
#include "libft.h"
#include "stdlib.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>

int	lst_size(t_data *data)
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
	t_env_node	*new_node;
	int			eq_ind;

	new_node = malloc(sizeof(t_env_node));
	if (!new_node)
		return (error_handler("malloc error"), NULL);
	new_node->key_value = key_value;
	new_node->next = NULL;
	eq_ind = get_first_ind(key_value, '=', 0);
	new_node->key = ft_substr(key_value, 0, eq_ind);
	if (!new_node->key)
		return (error_handler("malloc error"), NULL);
	new_node->value = ft_substr(key_value, eq_ind + 1, \
			ft_strlen(key_value) - eq_ind);
	if (!new_node->value)
		return (error_handler("malloc error"), NULL);
	if (lst_size(data) == 0)
		data->head = new_node;
	return (new_node);
}

t_env_node	*last_node(t_data *data)
{
	t_env_node	*temp;

	temp = data->head;
	while (temp && temp->next)
		temp = temp->next;
	return (temp);
}

void	update_node(t_env_node *node, char *key_value, int eq_ind)
{
	if (node)
	{
		free(node->key_value);
		free(node->value);
		node->key_value = key_value;
		node->value = ft_substr(key_value, eq_ind + 1, \
			ft_strlen(key_value) - eq_ind);
	}
}

int	add_env(t_data *data, char *key_value)
{
	t_env_node	*node;
	t_env_node	*lastnode;

	if (data->head && key_value)
	{
		node = new_node(data, key_value);
		if (!node)
			return (0);
		lastnode = last_node(data);
		lastnode->next = node;
	}
	return (1);
}
