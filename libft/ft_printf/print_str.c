/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:40:08 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/11/23 17:49:28 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_str_left(char *ch, int *wp, char *flags, int str_len)
{
	int	i;

	i = 0;
	if (flags[1] == '-')
	{
		if (ch == NULL && (wp[1] == -1 || wp[1] > 5))
			write(1, "(null)", 6);
		if (ch != NULL)
			write(1, ch, str_len);
		while (i < (wp[0] - str_len))
		{
			write(1, " ", 1);
			i++;
		}
	}
	return (i);
}

int	print_str_right(char *ch, int *wp, char *flags, int str_len)
{
	int	i;

	i = 0;
	if (flags[1] != '-')
	{
		while (i < (wp[0] - str_len))
		{
			write(1, " ", 1);
			i++;
		}
		if (ch == NULL && (wp[1] == -1 || wp[1] > 5))
			write(1, "(null)", 6);
		if (ch != NULL)
			write(1, ch, str_len);
	}
	return (i);
}

int	print_str(char *ch, int *wp, char *flags)
{
	int	str_len;
	int	i;

	if (ch == NULL)
		str_len = 6;
	else
		str_len = (int)ft_strlen(ch);
	if (wp[1] > -1 && wp[1] < str_len)
	{
		if (ch == NULL)
			str_len = 0;
		else if (ch != NULL)
			str_len = wp[1];
	}
	i = 0;
	i += print_str_left(ch, wp, flags, str_len);
	i += print_str_right(ch, wp, flags, str_len);
	return (str_len + i);
}
