/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:51:31 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/09/24 17:14:36 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	slen;
	size_t	restlen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	restlen = slen - start;
	if (start >= slen)
	{
		sub = ft_strdup("");
		return (sub);
	}
	if (restlen < len)
		len = restlen;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	ft_memcpy(sub, s + start, len);
	sub[len] = '\0';
	return (sub);
}
