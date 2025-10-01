/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 00:03:33 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/02/28 00:31:09 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	get_fraction(const char *nptr, int i)
{
	double	fraction;
	double	divisor;

	fraction = 0.0;
	divisor = 10.0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		++i;
	if (nptr[i] == '.')
	{
		++i;
		while (nptr[i] >= '0' && nptr[i] <= '9')
		{
			fraction += (nptr[i] - '0') / divisor;
			divisor *= 10.0;
			++i;
		}
	}
	return (fraction);
}

double	ft_atof(const char *nptr)
{
	double	int_part;
	double	fraction;
	int		sign;
	int		i;

	int_part = (double)ft_atoi(nptr);
	i = 0;
	sign = 1;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		++i;
	}
	fraction = get_fraction(nptr, i);
	return (int_part + sign * fraction);
}

// int	main(int argc, char **argv)
// {
// 	printf("%f/n", ft_atof(argv[1]));
// }