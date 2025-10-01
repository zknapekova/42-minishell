/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 23:25:23 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/11/23 21:05:28 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_ptr_len(uintptr_t num)
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

void	put_ptr(uintptr_t num)
{
	if (num >= 16)
	{
		put_ptr(num / 16);
		put_ptr(num % 16);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd((num + '0'), 1);
		else
			ft_putchar_fd((num - 10 + 'a'), 1);
	}
}

void	align_ptr_left(unsigned long long ptr, int width, int *ch_printed)
{
	int	dummy;

	dummy = 0;
	if (!ptr)
		*ch_printed += write(1, "(nil)", 5);
	else
	{
		*ch_printed += write(1, "0x", 2);
		put_ptr(ptr);
		*ch_printed += get_ptr_len(ptr);
	}
	while (*ch_printed < width)
		print_padding(' ', ch_printed, &dummy);
}

void	align_ptr_right(unsigned long long ptr, int width, int *ch_printed)
{
	int	len;
	int	dummy;

	dummy = 0;
	if (!ptr)
		len = 5;
	else
		len = get_ptr_len(ptr) + 2;
	while (*ch_printed < width - len)
	{
		print_padding(' ', ch_printed, &dummy);
	}
	if (!ptr)
		*ch_printed += write(1, "(nil)", 5);
	else
	{
		*ch_printed += write(1, "0x", 2);
		put_ptr(ptr);
		*ch_printed += get_ptr_len(ptr);
	}
}

int	print_ptr(unsigned long long ptr, char *flags, int width)
{
	int	ch_printed;

	ch_printed = 0;
	if (flags[1] == '-')
		align_ptr_left(ptr, width, &ch_printed);
	else
		align_ptr_right(ptr, width, &ch_printed);
	return (ch_printed);
}
