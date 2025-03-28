/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:24:56 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/09/21 16:05:31 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t			len_d;
	size_t			len_s;
	unsigned int	i;

	i = 0;
	len_d = ft_strlen(dest);
	len_s = ft_strlen(src);
	if (len_d >= size)
		return (size + len_s);
	while (src[i] && (len_d + i) < (size - 1))
	{
		dest[len_d + i] = src[i];
		++i;
	}
	dest[len_d + i] = '\0';
	return (len_s + len_d);
}

//  #include <string.h>
//  #include <stdio.h>
//  #include <unistd.h>
//  #include <bsd/string.h>
// 
// void	ft_print_result(int n)
// {
// 	char c;
// 
// 	if (n >= 10)
// 		ft_print_result(n / 10);
// 	c = n % 10 + '0';
// 	write (1, &c, 1);
// }
// 
// int	main(void)
// {
// 	char	dest[15];
// 
// 	memset(dest, 'r', 15);
// 	ft_print_result(ft_strlcat(dest, "lorem ipsum dolor sit amet", 5));
// 	write(1, "\n", 1);
// 	write(1, dest, 15);
// 	memset(dest, 'r', 15);
// 	ft_print_result(strlcat(dest, "lorem ipsum dolor sit amet", 5));
// 	write(1, "\n", 1);
// 	write(1, dest, 15);
// 	return (0);
// }