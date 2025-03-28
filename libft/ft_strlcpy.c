/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:00:41 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/07/19 17:34:24 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

// function follows the description in Linux man 5.10
size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	src_len;
	unsigned int	i;

	src_len = 0;
	i = 0;
	while (src[src_len] != '\0')
	{
		src_len++;
	}
	if (size == 0)
	{
		return (src_len);
	}
	while (i < (size - 1) && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_len);
}

// int	main(void)
// {
// 	char	dest[2000] = "abcdefg ;lk Bye";
// 	char	src[] = "Hello, World!";
// 	unsigned int	size = 100;
// 	unsigned int	len;
	// 
// 	len = ft_strlcpy(dest, src, size);
// 	printf("%s, %i\n", dest, len);
// 	return (0);
// }