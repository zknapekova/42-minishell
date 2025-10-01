/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:23:07 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/09/26 17:52:10 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ft_strmapi applies the function f on every character of the input string s
// characters are stored in a new string str
// if the original string s or the function f are missing,
// empty string is returned

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	i = 0;
	if (!s || !f)
	{
		str = ft_strdup("");
		return (str);
	}
	str = (char *)(malloc)(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
