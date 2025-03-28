/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:36:12 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/11/23 21:09:11 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	write_number(char *dec_str, int dec, int *ch_printed, int prec)
{
	if (!(!dec && !prec))
	{
		write(1, dec_str, ft_strlen(dec_str));
		(void)(*ch_printed += ft_strlen(dec_str));
	}
}

void	print_padding(char padding_char, int *ch_printed, int *p)
{
	write (1, &padding_char, 1);
	(void)((*ch_printed)++);
	(void)((*p)++);
}

void	print_space_on_left(int dec, int *ch_printed, int *wp)
{
	int		dummy;
	char	*dec_str;

	dummy = 0;
	dec_str = ft_itoa(dec);
	if (dec > 0)
		while (((*ch_printed < wp[0] - wp[1]) && \
		(wp[1] >= (int)ft_strlen(dec_str))) || \
		((*ch_printed < wp[0] - (int)ft_strlen(dec_str)) && \
		(wp[1] < (int)ft_strlen(dec_str))))
			print_padding(' ', ch_printed, &dummy);
	if (!dec)
		while (((*ch_printed < wp[0] - wp[1]) && wp[1] >= 0) || \
			((*ch_printed < wp[0] - 1) && wp[1] < 0))
			print_padding(' ', ch_printed, &dummy);
	if (dec < 0)
		while (((*ch_printed < wp[0] - wp[1] - 1) && \
		(wp[1] >= (int)ft_strlen(dec_str) - 1)) || \
		(*ch_printed < wp[0] - (int)ft_strlen(dec_str) && \
		(wp[1] < (int)ft_strlen(dec_str) - 1)))
			print_padding(' ', ch_printed, &dummy);
	free (dec_str);
}

void	uprint_space_on_left(unsigned int dec, int *ch_printed, int *wp)
{
	int		dummy;
	char	*dec_str;

	dummy = 0;
	dec_str = uitoa(dec);
	if (dec > 0)
		while (((*ch_printed < wp[0] - wp[1]) && \
		(wp[1] >= (int)ft_strlen(dec_str))) || \
		((*ch_printed < wp[0] - (int)ft_strlen(dec_str)) && \
		(wp[1] < (int)ft_strlen(dec_str))))
			print_padding(' ', ch_printed, &dummy);
	if (!dec)
		while (((*ch_printed < wp[0] - wp[1]) && wp[1] >= 0) || \
			((*ch_printed < wp[0] - 1) && wp[1] < 0))
			print_padding(' ', ch_printed, &dummy);
	free (dec_str);
}

int	print_char(int c, int width, char *flags)
{
	int	ch_printed;

	ch_printed = 0;
	if (flags[1] == '-')
	{
		ch_printed += write(1, &c, 1);
		while (width > 1)
		{
			ch_printed += write(1, " ", 1);
			width--;
		}
	}
	else
	{
		while (width > 1)
		{
			ch_printed += write(1, " ", 1);
			width--;
		}
		ch_printed += write(1, &c, 1);
	}
	return (ch_printed);
}
