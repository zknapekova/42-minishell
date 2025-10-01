/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:55:59 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/01/11 17:15:16 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft.h"
# include <stdarg.h>
# include <stdint.h>

int		ft_printf(const char *str, ...);
int		get_width(const char *str, int *i);
int		get_precision(const char *str, int *i);
int		print_char(int c, int width, char *flags);
int		print_str(char *ch, int *wp, char *flags);
int		print_dec(int dec, int *wp, char *flags);
void	print_sign(int *dec, char *flags, int *ch_printed);
void	print_padding(char padding_char, int *ch_printed, int *p);
int		print_ptr(unsigned long long ptr, char *flags, int width);
int		print_undec(int undec, int *wp, char *flags);
void	write_number(char *dec_str, int dec, int *ch_printed, int prec);
void	print_space_on_left(int dec, int *ch_printed, int *wp);
void	uprint_space_on_left(unsigned int dec, int *ch_printed, int *wp);
char	*uitoa(unsigned int n);
int		print_hex(unsigned int hexnum, int *wp, char *flags, char casech);
int		get_hex_len(unsigned int num);
void	put_hex(unsigned int num, char casech);
void	print_alt_format(char hash, char casech, int num, int *ch_printed);
int		print_percent(void);

#endif