/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:26:27 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/09/27 15:29:11 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int				i;
	char			str[12];
	unsigned int	num;

	i = 0;
	if (n == 0)
		write(fd, "0", 1);
	if (n < 0)
	{
		write(fd, "-", 1);
		num = (unsigned int)(-n);
	}
	else
		num = (unsigned int)n;
	while (num)
	{
		str[i] = (num % 10) + '0';
		num = num / 10;
		++i;
	}
	while (i)
	{
		write(fd, &str[i - 1], 1);
		--i;
	}
}
