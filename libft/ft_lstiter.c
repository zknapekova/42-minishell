/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 16:38:08 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/10/01 16:40:48 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*ptr;

	ptr = NULL;
	ptr = lst;
	while (ptr)
	{
		f(ptr -> content);
		ptr = ptr -> next;
	}
}
