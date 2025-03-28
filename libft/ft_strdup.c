/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:09:28 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/09/22 19:39:50 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;

	len = ft_strlen(s);
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, len);
	dup[len] = '\0';
	return (dup);
}

// int	main(void)
// {
// 	const char	*s = "abc";
// 	char	*dup = ft_strdup(s);
// 	printf("%s/n", dup);
// 	return (0);
// }