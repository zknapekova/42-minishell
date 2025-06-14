/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_rm_escape_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 19:32:42 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/07 22:10:41 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"

char	*rm_escape_char(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	if (!str || !str[0])
		return (NULL);
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new_str)
		return (error_handler("Error allocating new str in rm_escape_char"), \
		NULL);
	while (str[i])
	{
		if (str[i] == '\\')
			i++;
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

// adds \ before *
char	*escape_wildcard(char *str)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	result = malloc(sizeof(char) * 2 * (ft_strlen(str) + 1));
	if (!str)
		return (error_handler("Error in escape_wildcard()"), NULL);
	while (str[i])
	{
		if (str[i] == '*')
			result[j++] = '\\';
		result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}
