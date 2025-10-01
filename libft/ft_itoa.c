/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:43:04 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/09/25 19:18:31 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	num_casting(int n, int *i)
{
	unsigned int	num;

	if (n > 0)
		num = (unsigned int)n;
	if (n < 0 || n == 0)
	{
		num = (unsigned int)(-n);
		(*i)++;
	}
	return (num);
}

char	*ft_itoa(int n)
{
	int				i;
	char			*str;
	unsigned int	num;
	int				nn;

	i = 0;
	nn = n;
	num = num_casting(n, &i);
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
	if (nn < 0)
		str[0] = '-';
	return (str);
}

// int main(void)
//  {
//     // int	nbn = -2147483648;
// 	// int nbp = 2147483647;

// 	printf("%s\n", ft_itoa(-2147483648));
//     return 0;
//  }