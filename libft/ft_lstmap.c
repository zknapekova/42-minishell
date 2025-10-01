/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 22:55:32 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/10/02 18:21:45 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ptr;
	t_list	*new_list;
	t_list	*new_node;
	void	*new_content;

	new_list = NULL;
	if (!lst || !f || !del)
		return (NULL);
	ptr = lst;
	while (ptr)
	{
		new_content = ptr -> content;
		new_node = ft_lstnew(f(new_content));
		if (!new_node)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		ptr = ptr -> next;
	}
	return (new_list);
}

// // Function that will transform each element (e.g., multiply by 2)
// void *multiply_by_two(void *content)
// {
// 	int *new_value = malloc(sizeof(int));
// 	if (!new_value)
// 		return (NULL);
// 	*new_value = (*(int *)content) * 2;
// 	return (new_value);
// }

// // Function to free content
// void del(void *content)
// {
// 	free(content);
// }

// // Function to print the list (for debugging purposes)
// void print_list(t_list *lst)
// {
// 	while (lst)
// 	{
// 		printf("%d -> ", *(int *)(lst->content));
// 		lst = lst->next;
// 	}
// 	printf("NULL\n");
// }

// int main()
// {
// 	// Create a sample linked list: 1 -> 2 -> 3 -> NULL
// 	int a = 1, b = 2, c = 3;
// 	t_list *list = ft_lstnew(&a);
// 	ft_lstadd_back(&list, ft_lstnew(&b));
// 	ft_lstadd_back(&list, ft_lstnew(&c));

// 	printf("Original list: ");
// 	print_list(list);

// 	// Apply ft_lstmap with multiply_by_two
// 	t_list *mapped_list = ft_lstmap(list, multiply_by_two, del);

// 	printf("Mapped list (each element * 2): ");
// 	print_list(mapped_list);

// 	// Clean up memory
// 	ft_lstclear(&list, NULL);     
// // Original list was using stack-allocated data, no need for del
// 	ft_lstclear(&mapped_list, del); 
// // Mapped list was heap-allocated, so use del
// 	return (0);
// }