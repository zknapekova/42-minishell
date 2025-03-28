/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:45:21 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/07/19 17:52:08 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>

// ptr and s point to the same address in the memory,
// therefore, by manipulating ptr, we modify s
// In the ft_memset function, s is a pointer to a block of memory
// that you want to set to a particular value. By casting s to unsigned char* 
// and assigning it to ptr, you are creating a new pointer ptr that points to 
// the same memory location as s. Any changes made using ptr will directly 
// affect the memory that s points to.
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (s);
}

// int	main(void)
// {
// 	char	s[100] = "Hello world";
// 	int	c = '1';
// 	size_t n = 30;
	// 
// 	ft_memset(s, c, n);
// 	printf("%s, ", s);
// 	return (0);
// }