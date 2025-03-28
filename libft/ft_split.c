/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 17:19:54 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/02/09 20:13:38 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The ft_split trims the delimiting characters from the beginning and the end
// of the string. It alsou treats multiple consecutive delimiters as one.
// With empty string on input or when the string only contains delimiter
//  characters, empty 2D array is returned.
// If c is '\0', 2D array containing original string is returned.

// div_counter counts the number of future segments (divisions)
static int	div_counter(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	if (s[0] && s[0] != c)
		count++;
	while (i < ft_strlen(s))
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1])
			count++;
		i++;
	}
	return (count);
}

// segmentator function counts the length of each segment (substring),
//  allocates memory for it, and returns the substring.
// I am passing i into the segmentator as a pointer
//  so that its value is modified and returned

static char	*segmentator(char const *s, char c, size_t *i)
{
	size_t	j;
	size_t	k;
	char	*new_string;

	j = *i;
	while (s[*i] && s[*i] != c)
		(*i)++;
	new_string = (char *)malloc(sizeof(char) * (*i - j + 1));
	if (!new_string)
		return (NULL);
	k = 0;
	while (j != *i)
	{
		new_string[k] = s[j];
		k++;
		j++;
	}
	new_string[k] = '\0';
	return (new_string);
}

static void	free_array(char **array, size_t j)
{
	while (j > 0)
		free(array[--j]);
	free(array);
}

static int	fill_array(char **array, char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] != c)
		{
			array[j] = segmentator(s, c, &i);
			if (!array[j])
			{
				free_array(array, j);
				return (0);
			}
			j++;
		}
		else
			i++;
	}
	array[j] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**array;

	if (!s || !div_counter(s, c))
	{
		array = (char **)malloc(1 * sizeof(char *));
		array[0] = NULL;
		return (array);
	}
	array = (char **)malloc(sizeof(char *) * ((div_counter(s, c)) + 1));
	if (!array)
		return (NULL);
	if (!fill_array(array, s, c))
	{
		free_array(array, div_counter(s, c));
		return (NULL);
	}
	return (array);
}

// int 	main(void)
// {
// 	int i = 0;

// 	while (ft_split("hello!", ' ')[i])
// 	{
// 		printf("%s", ft_split("hello!", ' ')[i]);
// 		i++;
// 	}
// 	return (0);
// }