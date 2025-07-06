/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 21:40:33 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/07/06 23:15:25 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"

t_bool	is_n_flag(char *str);

void	normalize_n_flag(char **input)
{
	int		read;
	int		write;
	t_bool	found_n_flag;

	read = 1;
	write = 1;
	found_n_flag = false;
	while (input[read] && is_n_flag(input[read]))
	{
		free(input[read]);
		read++;
		found_n_flag = true;
	}
	if (found_n_flag == true)
		input[write++] = ft_strdup("-n");
	while (input[read])
		input[write++] = input[read++];
	input[write] = NULL;
}

t_bool	is_n_flag(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (false);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}
