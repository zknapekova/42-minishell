/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_percent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:54:03 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/04/17 16:17:25 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_eprintf.h"

int	eprint_percent(void)
{
	int	ch_printed;

	ch_printed = 0;
	write(2, "%", 1);
	ch_printed++;
	return (ch_printed);
}
