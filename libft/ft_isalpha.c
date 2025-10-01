/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:13:53 by jgrigorj          #+#    #+#             */
/*   Updated: 2024/07/12 00:22:08 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}

// #include <stdio.h>
// #include <ctype.h>
// int	main(void)
// {
// 	char ch = 'a';
// 	while (ch >= 'a' && ch <= 123)
// 	{
// 		printf("%d, %d\n", isalpha(ch), ft_isalpha(ch));
// 		++ch;
// 	}
// 	return (0);
// }