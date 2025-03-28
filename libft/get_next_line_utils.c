/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:03:14 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/01/27 22:13:55 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_ed(char const *s1, char const *s2, int len2)
{
	size_t	len1;
	char	*str;

	len1 = ft_strlen(s1);
	str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
	{
		free((char *)s1);
		return (NULL);
	}
	if (s1)
	{
		ft_memcpy(str, s1, len1);
		free ((char *)s1);
	}
	ft_memcpy(str + len1, s2, len2);
	str[len1 + len2] = '\0';
	return (str);
}

// size_t	ft_strlen(const char *str)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		++i;
// 	}
// 	return (i);
// }

size_t	check_endline(char *buffer)
{
	size_t	i;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (i);
		i++;
	}
	return (++i);
}
