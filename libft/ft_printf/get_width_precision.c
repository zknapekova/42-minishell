/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_width_precision.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 20:21:10 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/11/20 20:24:47 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_width(const char *str, int *i)
{
	int	width;

	width = 0;
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		width = width * 10 + (str[*i] - 48);
		(*i)++;
	}
	return (width);
}

int	get_precision(const char *str, int *i)
{
	int	prec;

	prec = -1;
	if (str[*i] == '.')
	{
		prec = 0;
		(*i)++;
		while (str[*i] >= '0' && str[*i] <= '9')
		{
			prec = prec * 10 + (str[*i] - 48);
			(*i)++;
		}
	}
	return (prec);
}
