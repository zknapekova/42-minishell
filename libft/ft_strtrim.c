/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:18:08 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/09/26 17:17:40 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	to_trim(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		from_start;
	int		to_end;

	if (!s1)
	{
		str = ft_strdup("");
		return (str);
	}
	from_start = 0;
	to_end = ft_strlen(s1) - 1;
	while (to_trim(set, s1[from_start]))
		from_start++;
	while (to_trim(set, s1[to_end]) && to_end >= 0)
		to_end--;
	if (from_start > to_end)
	{
		str = ft_strdup("");
		return (str);
	}
	str = ft_substr(s1, from_start, to_end - from_start + 1);
	return (str);
}

// int	main(void)
// {
// 	char const *s1 = "";
// 	char const *set = "";

// 	printf("t%st\n", ft_strtrim(s1, set));
// 	return (0);	
// }