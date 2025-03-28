/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:13:53 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/07/12 00:58:53 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

// #include <stdio.h>
// #include <ctype.h>
// int	main(void)
// {
// 	char ch = '0';
// 	while (ch >= '0' && ch <= '9')
// 	{
// 		printf("%d, %d\n", isdigit(ch), ft_isdigit(ch));
// 		++ch;
// 	}
// 	return (0);
// }