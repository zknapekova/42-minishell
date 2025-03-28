/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:33:39 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/10/02 17:45:29 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		++i;
	}
	return (i);
}

// #include <stdio.h>
// 
// int	main(void)
// {
// 	char	str[] = "";
	// 
// 	printf("%zu\n", ft_strlen(str));
// 	return (0);
// }