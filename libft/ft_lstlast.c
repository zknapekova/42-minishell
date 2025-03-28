/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:11:51 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/10/01 14:37:41 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*ptr;

	if (!lst)
		return (lst);
	ptr = NULL;
	ptr = lst;
	while (ptr -> next)
	{
		ptr = ptr -> next;
	}
	return (ptr);
}
