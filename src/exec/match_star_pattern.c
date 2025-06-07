/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_star_pattern.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 21:53:09 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/07 22:49:13 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> //for NULL
#include "libft.h"

static void	advance(char **pattern, char **str);
static void	fallback(char **pattern, char **str, char **backup, char *star);
static void	save_star_pos(char **star, \
	char **pattern, char **backup, char *str);
static int	handle_escape(char **pattern, char **str);

int	match_star_pattern(char *pattern, char *str)
{
	char	*star;
	char	*backup;

	star = NULL;
	backup = NULL;
	if (ft_strncmp(pattern, "./", 2) == 0)
		pattern += 2;
	while (*str)
	{
		if (!handle_escape(&pattern, &str))
			return (0);
		else if (*pattern == '*')
			save_star_pos(&star, &pattern, &backup, str);
		else if (*pattern == *str)
			advance(&pattern, &str);
		else if (star)
			fallback(&pattern, &str, &backup, star);
		else
			return (0);
	}
	while (*pattern == '*')
		pattern++;
	return (*pattern == '\0');
}

static void	advance(char **pattern, char **str)
{
	(*pattern)++;
	(*str)++;
}

static void	fallback(char **pattern, char **str, char **backup, char *star)
{
	*pattern = star + 1;
	*str = ++(*backup);
}

static void	save_star_pos(char **star, char **pattern, char **backup, char *str)
{
	*star = (*pattern)++;
	*backup = str;
}

static int	handle_escape(char **pattern, char **str)
{
	if (**pattern == '\\' && *(*pattern + 1) == '*')
	{
		*pattern += 2;
		if (**str != '*')
			return (0);
		(*str)++;
	}
	return (1);
}
