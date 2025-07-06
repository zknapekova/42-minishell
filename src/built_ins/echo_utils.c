/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 21:40:33 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/07/06 21:40:34 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	normalize_n_flag(char **input)
{
	int	i;

	if (input && input[1])
	{
		if (input[1][0] == '-' && input[1][1] == 'n')
		{
			i = 2;
			while (input[1][i])
			{
				if (input[1][i] != 'n')
					return ;
				i++;
			}
			free(input[1]);
			input[1] = ft_strdup("-n");
		}
	}
}
