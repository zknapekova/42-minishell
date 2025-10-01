/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:55:59 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/07/06 21:29:44 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EPRINTF_H
# define FT_EPRINTF_H

# include "../libft.h"
# include <stdarg.h>
# include <stdint.h>

int		ft_eprintf(const char *str, ...);
int		eget_width(const char *str, int *i);
int		eget_precision(const char *str, int *i);
int		eprint_char(int c, int width, char *flags);
int		eprint_str(char *ch, int *wp, char *flags);
int		eprint_dec(int dec, int *wp, char *flags);
void	eprint_sign(int *dec, char *flags, int *ch_printed);
void	eprint_padding(char padding_char, int *ch_printed, int *p);
int		eprint_ptr(unsigned long long ptr, char *flags, int width);
int		eprint_undec(int undec, int *wp, char *flags);
void	ewrite_number(char *dec_str, int dec, int *ch_printed, int prec);
void	eprint_space_on_left(int dec, int *ch_printed, int *wp);
void	euprint_space_on_left(unsigned int dec, int *ch_printed, int *wp);
char	*euitoa(unsigned int n);
int		eprint_hex(unsigned int hexnum, int *wp, char *flags, char casech);
int		eget_hex_len(unsigned int num);
void	eput_hex(unsigned int num, char casech);
void	eprint_alt_format(char hash, char casech, int num, int *ch_printed);
int		eprint_percent(void);

#endif