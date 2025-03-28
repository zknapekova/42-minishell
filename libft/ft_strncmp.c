/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:48:45 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/09/19 17:43:55 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	if (!n)
		return (0);
	if (s1[0] == '\0' && s2[0] == '\0')
	{
		return (0);
	}
	while (i < (n - 1) && s1[i] == s2[i] && s1[i])
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// #include <string.h>
// int	main(void)
// {
// 	char	str1[] = "test\200";
// 	char	str2[] = "test\0";
// 	size_t	n;
// 
//     n = 6;
// 	printf("s1 is %s, s2 is %s\n", str1, str2);
// 	printf("The difference is %i\n", ft_strncmp(str1, str2, n));
// 		printf("The difference is %i\n", strncmp(str1, str2, n));

// 	return (0);
// }