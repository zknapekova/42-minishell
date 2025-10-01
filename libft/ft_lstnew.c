/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:42:15 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/09/30 22:08:03 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// ft_lstnew creates a new node with given content
t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

// // Example usage of the create_node function
// int main()
// {
//     // Example content (in this case, an integer)
//     int *value = (int *)malloc(sizeof(int));
//     *value = 42;

//     // Create a new node with the integer content
//     t_list *node = ft_lstnew(value);

//     // Print the content of the node (casting void* to int*)
//     if (node)
//     {
//         printf("Node content: %d\n", *(int *)(node->content));
//     }

//     // Free allocated memory
//     free(value);
//     free(node);

//     return 0;
// }
