/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_percent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:54:22 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/05/18 23:23:43 by jgrigorj         ###   ########.fr       */
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
