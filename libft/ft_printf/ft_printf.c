/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:03:22 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/11/23 19:54:58 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_flags(const char *str, int *i, char *flags)
{
	ft_strlcpy(flags, "00000", 6);
	while (str[*i] == '+' || str[*i] == '-' || str[*i] == '0' \
		|| str[*i] == ' ' || str[*i] == '#')
	{
		if (str[*i] == '+')
			flags[0] = '+';
		else if (str[*i] == '-')
			flags[1] = '-';
		else if (str[*i] == '0')
			flags[2] = 'z';
		else if (str[*i] == ' ')
			flags[3] = ' ';
		else if (str[*i] == '#')
			flags[4] = '#';
		(*i)++;
	}
}

int	print_format(const char *str, va_list args, int *i, char *flags)
{
	int	ch_printed;
	int	wp[2];

	ch_printed = 0;
	wp[0] = get_width(str, i);
	wp[1] = get_precision(str, i);
	if (str[*i] == 'c')
		ch_printed += print_char(va_arg(args, int), wp[0], flags);
	else if (str[*i] == 's')
		ch_printed += print_str(va_arg(args, char *), wp, flags);
	else if (str[*i] == 'p')
		ch_printed += print_ptr(va_arg(args, unsigned long long), flags, wp[0]);
	else if (str[*i] == 'd' || str[*i] == 'i')
		ch_printed += print_dec(va_arg(args, int), wp, flags);
	else if (str[*i] == 'u')
		ch_printed += print_undec(va_arg(args, unsigned int), wp, flags);
	else if (str[*i] == 'x' || str[*i] == 'X')
		ch_printed += print_hex(va_arg(args, unsigned int), wp, flags, str[*i]);
	else if (str[*i] == '%')
		ch_printed += print_percent();
	else
		return (-1);
	return (ch_printed);
}

int	write_nfchar(const char *str, int *i)
{
	int	ch_printed;

	ch_printed = 0;
	while (str[*i] && str[*i] != '%')
	{
		write(1, &str[*i], 1);
		ch_printed++;
		(*i)++;
	}
	return (ch_printed);
}

int	ft_printf(const char *str, ...)
{
	int		ch_printed;
	va_list	args;
	int		i;
	char	flags[6];

	ch_printed = 0;
	i = 0;
	if (str == NULL)
		return (-1);
	va_start(args, str);
	while (str[i])
	{
		ch_printed += write_nfchar(str, &i);
		if (str[i] == '%')
		{
			i++;
			get_flags(str, &i, flags);
			ch_printed += print_format(str, args, &i, flags);
			i++;
		}
	}
	va_end(args);
	return (ch_printed);
}
