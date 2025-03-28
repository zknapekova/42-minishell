/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:45:21 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/09/24 16:00:12 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>

// If src starts before dest in memory, we assume that the end of 
// src may overlap the beginning of dest
// therefore, we need to start copying from the end of src.
// If src starts after dest in memory, we assume the opposite overlap
// and we copy from the beginnig of src.
// We cannot use the temporary array as indicated by the man, since
// it would require the use of malloc. Cannot initialize it as char temp[n].

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	if (!src && !dest && n > 0)
		return (NULL);
	if (src < dest)
	{
		while (n-- > 0)
		{
			d[n] = s[n];
		}
	}
	else
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}

// int	main(void)
// {
// 	char	src[100] = "Hello world";
// 	char 	dest[100] = "abc" ;
// 	size_t n = 30;
// 
// 	ft_memmove(dest, src, n);
// 	printf("%s ", dest);
// 	return (0);
// }