/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:02:49 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/09/21 16:22:33 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*source;
	unsigned char		ch;

	i = 0;
	source = (const unsigned char *)s;
	ch = (unsigned char)c;
	while (i < n)
	{
		if (source[i] == ch)
			return ((void *)&source[i]);
		i++;
	}
	return (NULL);
}
// #include <string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char buffer[12] = { 'h', 'e', 'l', 'l', 'o', 0, 'w', 'o', 'r', 'l'};
// 	char *p = memchr(buffer, 'x', 15);  
// 	if (p != NULL) // Check if 'w' was found
// 		printf("%s\n", p);
// 	else
// 		printf("Character not found within the first 15 bytes.\n");
// 	return (0);
// }