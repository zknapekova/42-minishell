/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 18:58:14 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/09/23 16:01:22 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*str;
	size_t	i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		str[len1 + i] = s2[i];
		i++;
	}
	str[len1 + i] = '\0';
	return (str);
}

// int	main(void)
// {
// 	char	s1[] = "lorem ipsum";
// 	char	s2[] = "dolor sit amet";
// 	char	*strjoin;

// 	strjoin = ft_strjoin(s1, s2);
// 	printf("%s\n", strjoin);
// 	return (0);
// }
