/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:22:10 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/04/17 16:20:27 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eprintf.h"

static int	align_hex_left(unsigned int num, char *flags, int *wp, char casech)
{
	int	ch_printed;
	int	p;

	ch_printed = 0;
	p = 0;
	if (!(!num && !wp[1]))
	{
		eprint_alt_format(flags[4], casech, num, &ch_printed);
		while ((!num && p < wp[1]) || \
		(num && p < wp[1] - eget_hex_len(num)))
			eprint_padding('0', &ch_printed, &p);
		if (num || wp[1] == -1)
			eput_hex(num, casech);
		ch_printed += eget_hex_len(num);
		if (!num && wp[1] == -1)
			ch_printed++;
	}
	while (ch_printed < wp[0])
		eprint_padding(' ', &ch_printed, &p);
	return (ch_printed);
}

static void	print_space_hex(unsigned int num, char *flags, \
	int *wp, int *ch_printed)
{
	int	dummy;

	dummy = 0;
	if (num > 0)
	{
		if (flags[4] == '#')
			(*ch_printed) += 2;
		while (((*ch_printed < wp[0] - wp[1]) && \
		(wp[1] >= eget_hex_len(num))) || \
		((*ch_printed < wp[0] - eget_hex_len(num)) && \
		(wp[1] < eget_hex_len(num))))
			eprint_padding(' ', ch_printed, &dummy);
	}
	if (!num)
		while (((*ch_printed < wp[0] - wp[1]) && wp[1] >= 0) || \
			((*ch_printed < wp[0]) && wp[1] < 0))
			eprint_padding(' ', ch_printed, &dummy);
}

static void	prec_padding(unsigned int num, int *wp, int *ch_printed)
{
	int	p;

	p = 0;
	while (((p < wp[1] - eget_hex_len(num)) && num) || \
	((p < wp[1]) && !num))
		eprint_padding('0', ch_printed, &p);
}

static int	align_hex_right(unsigned int num, char *flags, int *wp, char casech)
{
	int	ch_printed;
	int	p;

	ch_printed = 0;
	p = 0;
	if (!num && wp[1] == -1)
		ch_printed++;
	if (wp[1] < 0 && flags[2] == 'z')
	{
		eprint_alt_format(flags[4], casech, num, &ch_printed);
		while (((ch_printed < wp[0] - eget_hex_len(num)) && num) || \
		((ch_printed < wp[0]) && !num))
			eprint_padding('0', &ch_printed, &p);
	}
	print_space_hex(num, flags, wp, &ch_printed);
	if (!(flags[2] == 'z' && wp[1] < 0))
		eprint_alt_format(flags[4], casech, num, &ch_printed);
	if (flags[4] == '#' && num)
		ch_printed -= 2;
	prec_padding(num, wp, &ch_printed);
	if (num || wp[1] == -1)
		eput_hex(num, casech);
	ch_printed += eget_hex_len(num);
	return (ch_printed);
}

int	eprint_hex(unsigned int num, int *wp, char *flags, char casech)
{
	int	ch_printed;

	ch_printed = 0;
	if (flags[1] == '-')
		ch_printed += align_hex_left(num, flags, wp, casech);
	else
		ch_printed += align_hex_right(num, flags, wp, casech);
	return (ch_printed);
}
