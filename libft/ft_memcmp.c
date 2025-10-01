/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:45:40 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/09/21 17:21:40 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*suc1;
	unsigned char	*suc2;
	size_t			i;

	suc1 = (unsigned char *)s1;
	suc2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (suc1[i] != suc2[i])
			return ((int)(suc1[i] - suc2[i]));
		i++;
	}
	return (0);
}

// #include <string.h>
// int	main(void)
// {
// 	char	str1[] = "testtes";
// 	char	str2[] = "testtes";
// 	size_t	n;

//     n = 9;
// 	printf("s1 is %s, s2 is %s\n", str1, str2);
// 	printf("The difference is %i\n", ft_memcmp(str1, str2, n));
// 		printf("The difference is %i\n", memcmp(str1, str2, n));
// 	return (0);
// }
