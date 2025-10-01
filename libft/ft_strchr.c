/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:45:21 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/09/27 15:30:12 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//  The ft_strchr() function returns a pointer to the first occurrence
//  of the character c in the string s.
// also possible to replace (char *)&s[i] with just &s[i]
// &s[i] is simply the getting the part of the string starting at i
// s[i] would be just one character
// The NULL pointer is defined in the stdio library imported in libft.h
char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	ch;

	i = 0;
	ch = (unsigned char)c;
	if (ch == '\0')
	{
		while (s[i])
		{
			i++;
		}
		return ((char *)&s[i]);
	}
	while (s[i])
	{
		if (s[i] == ch)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}
// int	main(void)
// {
// 	const char	*s;
// 	int	c = 'l';

// 	s =  "Hello world";
// 	printf("%s ", ft_strchr(s, c));
// 	return (0);
// }