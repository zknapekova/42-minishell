/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 20:04:12 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/07 22:55:20 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"
#include "exec.h"

int	is_in_cwd(char *str)
{
	if (!ft_strchr(str, '/'))
		return (1);
	if (str[0] == '.' && str[1] == '/')
	{
		if (!ft_strchr(str + 2, '/'))
			return (1);
		else
			return (0);
	}
	return (0);
}

int	is_hidden_file(char *str)
{
	return ((str[0] == '.' && str[1] != '/') \
	|| (str[0] == '.' && str[1] == '/' && str[2] == '.'));
}

t_file	*sort_file_list(t_file *head)
{
	t_file	*sorted;
	t_file	*next;

	sorted = NULL;
	while (head)
	{
		next = head->next;
		head->next = NULL;
		sorted = sorted_insert(sorted, head);
		head = next;
	}
	return (sorted);
}

// insert sort
t_file	*sorted_insert(t_file *head, t_file *new_node)
{
	t_file	*current;

	if (!head || ft_strncmp(new_node->name, head->name, \
		longer_strlen(new_node->name, head->name)) < 0)
	{
		new_node->next = head;
		return (new_node);
	}
	current = head;
	while (current->next && ft_strncmp(new_node->name, current->next->name, \
		longer_strlen(new_node->name, current->next->name)) > 0)
		current = current->next;
	new_node->next = current->next;
	current->next = new_node;
	return (head);
}

int	longer_strlen(char *str1, char *str2)
{
	if (!str1 || !str2)
		return (0);
	if (ft_strlen(str1) >= ft_strlen(str2))
		return (ft_strlen(str1));
	else
		return (ft_strlen(str2));
}
