/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:46:25 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/10/01 15:01:52 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*ptr_last;

	ptr_last = ft_lstlast(*lst);
	if (!ptr_last)
	{
		*lst = new;
		return ;
	}
	ptr_last -> next = new;
}
