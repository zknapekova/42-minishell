/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 18:04:39 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/09/21 21:03:50 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*little)
		return ((char *)big);
	i = 0;
	while (big[i] != 0 && i < len)
	{
		j = 0;
		while (little[j] != '\0' && i + j < len && big[i + j] == little[j])
		{
			j++;
			if (little[j] == '\0')
				return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}

// #include <string.h>
// #include <bsd/string.h>
// 
// int	main(void)
// {
// 	const char *largestring = "Foo Bar Baz Kiz";
// 	const char *smallstring = "Bur";
// 	char *ptr;
// 	// char *ptr1;
// 
// 	ptr = ft_strnstr(largestring, smallstring, 15);
// 	if (ptr != NULL)
// 		printf("%s\n", ptr);
// 	else
// 		printf("No match found\n");
// 	// ptr1 = strnstr(largestring, smallstring, 4);
// 	// if (ptr1 != NULL)
// 	// 	printf("%s", ptr1);
// 	// else
// 	// 	printf("No match found\n");
// 	return (0);
// }