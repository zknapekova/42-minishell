/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 21:09:38 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/01/26 21:48:16 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// this implementation does not handle edge values (> INT_MAX or < INT_MIN)
int	ft_atoi(const char *nptr)
{
	int	num;
	int	i;
	int	sign;

	num = 0;
	i = 0;
	sign = 1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
	{
		++i;
	}
	if (nptr[i] == '-')
	{
		sign = -1;
		++i;
	}
	else if (nptr[i] == '+')
		++i;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = num * 10 + (nptr[i] - 48);
		++i;
	}
	num = num * sign;
	return (num);
}

// int main(void)
// {
// 	char str[] = " \n3147483649";
// 	printf("%i\n", ft_atoi(str));
//     printf("%i\n", atoi(str));
// 	return 0;
// }