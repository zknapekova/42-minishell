/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 20:35:54 by zuknapek          #+#    #+#             */
/*   Updated: 2025/04/22 22:05:24 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/main.h"
#include "../include/token.h"
#include <stdlib.h>

static void	free_ll(t_data *data)
{
	t_env_node	*temp;

	if (data->head)
	{
		while (data->head)
		{
			temp = data->head->next;
			free(data->head);
			data->head = temp;
		}
	}
}

void	free_all(t_data *data)
{
	free_ll(data);
	free_token_list(data->tokens);
	free(data);
}