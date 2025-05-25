/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuknapek <zuknapek@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:41:41 by zuknapek          #+#    #+#             */
/*   Updated: 2025/05/04 15:41:27 by zuknapek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

int	get_first_ind(char *str, char c, int start)
{
	int	i;

	i = start;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	get_first_non_alnum(char *str, int start)
{
	int	i;

	i = start;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (i);
		i++;
	}
	return (i);
}

char	*add_new_line(char *str)
{
	char	*res;

	res = NULL;
	if (str)
		res = ft_strjoin(str, "\n");
	return (res);
}