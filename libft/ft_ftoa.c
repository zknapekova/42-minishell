/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:59:33 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/03/10 19:00:35 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_digits(float num, int precision)
{
	int	digits;

	digits = 0;
	if (num < 0)
	{
		digits++;
		num *= -1;
	}
	if (num > 0 && num < 1)
		digits++;
	while ((int)num)
	{
		num /= 10;
		digits++;
	}
	return (digits + precision + 1);
}

void	build_frac_str(char *num_str, float num, int precision, int digits)
{
	int	i;
	int	multiplier;

	i = -1;
	multiplier = 1;
	while (i < precision)
	{
		i++;
		multiplier *= 10;
	}
	num *= multiplier;
	i = digits - 1;
	while (i > digits - precision - 1)
	{
		num_str[i--] = ((int)num % 10) + '0';
		num /= 10;
	}
}

int	handle_sign(float *num)
{
	int	sign;

	sign = 1;
	if (*num < 0)
	{
		sign = -1;
		*num = -(*num);
	}
	return (sign);
}

char	*ft_ftoa(float num, int precision)
{
	int		digits;
	char	*num_str;
	int		sign;
	int		i;

	digits = get_digits(num, precision);
	num_str = malloc(sizeof(char) * (digits + 1));
	if (!num_str)
		return (NULL);
	num_str[digits] = '\0';
	sign = handle_sign(&num);
	i = digits - precision - 1;
	num_str[i] = '.';
	while (--i >= 0)
	{
		num_str[i] = ((int)num % 10) + '0';
		num /= 10;
	}
	build_frac_str(num_str, num, precision, digits);
	if (sign == -1)
		num_str[0] = '-';
	return (num_str);
}
