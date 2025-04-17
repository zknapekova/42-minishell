/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 21:00:22 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/04/17 16:16:43 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eprintf.h"

int	eget_hex_len(unsigned int num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

void	eput_hex(unsigned int num, char casech)
{
	if (num >= 16)
	{
		eput_hex(num / 16, casech);
		eput_hex(num % 16, casech);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd((num + '0'), 1);
		else
		{
			if (casech == 'x')
				ft_putchar_fd((num - 10 + 'a'), 1);
			else
				ft_putchar_fd((num - 10 + 'A'), 1);
		}
	}
}

void	eprint_alt_format(char hash, char casech, int num, int *ch_printed)
{
	if (hash == '#' && num)
	{
		if (casech == 'x')
			write(2, "0x", 2);
		if (casech == 'X')
			write(2, "0X", 2);
		(*ch_printed) += 2;
	}
}
