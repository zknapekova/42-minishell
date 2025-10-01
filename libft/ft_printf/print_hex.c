/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:22:10 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/11/23 21:02:38 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	align_hex_left(unsigned int num, char *flags, int *wp, char casech)
{
	int	ch_printed;
	int	p;

	ch_printed = 0;
	p = 0;
	if (!(!num && !wp[1]))
	{
		print_alt_format(flags[4], casech, num, &ch_printed);
		while ((!num && p < wp[1]) || \
		(num && p < wp[1] - get_hex_len(num)))
			print_padding('0', &ch_printed, &p);
		if (num || wp[1] == -1)
			put_hex(num, casech);
		ch_printed += get_hex_len(num);
		if (!num && wp[1] == -1)
			ch_printed++;
	}
	while (ch_printed < wp[0])
		print_padding(' ', &ch_printed, &p);
	return (ch_printed);
}

void	print_space_hex(unsigned int num, char *flags, int *wp, int *ch_printed)
{
	int	dummy;

	dummy = 0;
	if (num > 0)
	{
		if (flags[4] == '#')
			(*ch_printed) += 2;
		while (((*ch_printed < wp[0] - wp[1]) && \
		(wp[1] >= get_hex_len(num))) || \
		((*ch_printed < wp[0] - get_hex_len(num)) && \
		(wp[1] < get_hex_len(num))))
			print_padding(' ', ch_printed, &dummy);
	}
	if (!num)
		while (((*ch_printed < wp[0] - wp[1]) && wp[1] >= 0) || \
			((*ch_printed < wp[0]) && wp[1] < 0))
			print_padding(' ', ch_printed, &dummy);
}

void	prec_padding(unsigned int num, int *wp, int *ch_printed)
{
	int	p;

	p = 0;
	while (((p < wp[1] - get_hex_len(num)) && num) || \
	((p < wp[1]) && !num))
		print_padding('0', ch_printed, &p);
}

int	align_hex_right(unsigned int num, char *flags, int *wp, char casech)
{
	int	ch_printed;
	int	p;

	ch_printed = 0;
	p = 0;
	if (!num && wp[1] == -1)
		ch_printed++;
	if (wp[1] < 0 && flags[2] == 'z')
	{
		print_alt_format(flags[4], casech, num, &ch_printed);
		while (((ch_printed < wp[0] - get_hex_len(num)) && num) || \
		((ch_printed < wp[0]) && !num))
			print_padding('0', &ch_printed, &p);
	}
	print_space_hex(num, flags, wp, &ch_printed);
	if (!(flags[2] == 'z' && wp[1] < 0))
		print_alt_format(flags[4], casech, num, &ch_printed);
	if (flags[4] == '#' && num)
		ch_printed -= 2;
	prec_padding(num, wp, &ch_printed);
	if (num || wp[1] == -1)
		put_hex(num, casech);
	ch_printed += get_hex_len(num);
	return (ch_printed);
}

int	print_hex(unsigned int num, int *wp, char *flags, char casech)
{
	int	ch_printed;

	ch_printed = 0;
	if (flags[1] == '-')
		ch_printed += align_hex_left(num, flags, wp, casech);
	else
		ch_printed += align_hex_right(num, flags, wp, casech);
	return (ch_printed);
}
