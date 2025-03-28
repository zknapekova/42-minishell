/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:36:31 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/11/23 19:58:50 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_sign(int *dec, char *flags, int *ch_printed)
{
	if (*dec < 0)
	{
		write(1, "-", 1);
		if (*dec != -2147483648)
			*dec = -(*dec);
		(void)((*ch_printed)++);
	}
	else if (flags[0] == '+')
	{
		write(1, "+", 1);
		(void)((*ch_printed)++);
	}
}

void	align_dec_left(int dec, char *flags, int *wp, int *ch_printed)
{
	int		p;
	char	*dec_str;

	p = 0;
	print_sign(&dec, flags, ch_printed);
	dec_str = ft_itoa(dec);
	if (dec == -2147483648)
		ft_strlcpy(dec_str, "2147483648", 11);
	while (p < wp[1] - (int)ft_strlen(dec_str))
		print_padding('0', ch_printed, &p);
	write_number(dec_str, dec, ch_printed, wp[1]);
	while (*ch_printed < wp[0])
		print_padding(' ', ch_printed, &p);
	free (dec_str);
}

void	align_dec_right(int dec, char *flags, int *wp, int *ch_printed)
{
	int		p;
	int		dummy;
	char	*dec_str;

	p = 0;
	dummy = 0;
	dec_str = ft_itoa(dec);
	if (flags[3] == ' ' && dec >= 0 && flags[0] != '+')
		print_padding(' ', ch_printed, &dummy);
	if (wp[1] >= 0 || flags[2] != 'z')
		print_space_on_left(dec, ch_printed, wp);
	print_sign(&dec, flags, ch_printed);
	free (dec_str);
	dec_str = ft_itoa(dec);
	if (dec == -2147483648)
		ft_strlcpy(dec_str, "2147483648", 11);
	if (wp[1] < 0 && flags[2] == 'z')
		while (*ch_printed < wp[0] - (int)ft_strlen(dec_str))
			print_padding('0', ch_printed, &p);
	while (((p < wp[1] - (int)ft_strlen(dec_str))))
		print_padding('0', ch_printed, &p);
	write_number(dec_str, dec, ch_printed, wp[1]);
	free (dec_str);
}

int	print_dec(int dec, int *wp, char *flags)
{
	int	ch_printed;

	ch_printed = 0;
	if (flags[1] == '-')
		align_dec_left(dec, flags, wp, &ch_printed);
	else
		align_dec_right(dec, flags, wp, &ch_printed);
	return (ch_printed);
}
