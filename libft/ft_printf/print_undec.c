/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_undec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 00:29:55 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/11/23 21:06:21 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*uitoa(unsigned int n)
{
	int				i;
	char			*str;
	unsigned int	num;

	i = 0;
	num = n;
	if (!n)
		i++;
	while (n)
	{
		n = n / 10;
		++i;
	}
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i] = '\0';
	while (--i >= 0)
	{
		str[i] = (num % 10) + '0';
		num = num / 10;
	}
	return (str);
}

void	align_undec_left(unsigned int undec, int *wp, int *ch_printed)
{
	int		p;
	char	*undec_str;

	p = 0;
	undec_str = uitoa(undec);
	while (p < wp[1] - (int)ft_strlen(undec_str))
		print_padding('0', ch_printed, &p);
	write_number(undec_str, undec, ch_printed, wp[1]);
	while (*ch_printed < wp[0])
		print_padding(' ', ch_printed, &p);
	free (undec_str);
}

void	align_undec_right(int undec, char *flags, int *wp, int *ch_printed)
{
	int		p;
	char	*undec_str;

	p = 0;
	undec_str = uitoa(undec);
	if (wp[1] < 0 && flags[2] == 'z')
		while (((*ch_printed < wp[0] - (int)ft_strlen(undec_str))))
			print_padding('0', ch_printed, &p);
	uprint_space_on_left(undec, ch_printed, wp);
	while (((p < wp[1] - (int)ft_strlen(undec_str))))
		print_padding('0', ch_printed, &p);
	write_number(undec_str, undec, ch_printed, wp[1]);
	free (undec_str);
}

int	print_undec(int undec, int *wp, char *flags)
{
	int	ch_printed;

	ch_printed = 0;
	if (flags[1] == '-')
		align_undec_left(undec, wp, &ch_printed);
	else
		align_undec_right(undec, flags, wp, &ch_printed);
	return (ch_printed);
}
