/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:26:20 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/09/19 15:46:14 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// also possible to replace (char *)&s[i] with just &s[i]
// &s[i] is simply the getting the part of the string starting at i
// s[i] would be just one character
// The NULL pointer is defined in the stdio library imported in libft.h
char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	ch;
	char			*last;

	i = 0;
	last = NULL;
	ch = (unsigned char)c;
	if (ch == '\0')
	{
		while (s[i])
		{
			i++;
		}
		last = (char *)&s[i];
	}
	while (s[i])
	{
		if (s[i] == ch)
			last = (char *)&s[i];
		i++;
	}
	return (last);
}
// int	main(void)
// {
// 	const char	*s;
// 	int	c = 'x';

// 	s =  "Hello world";
// 	printf("%s ", ft_strrchr(s, c));
// 	return (0);
// }