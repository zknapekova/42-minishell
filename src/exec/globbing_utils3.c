/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 19:38:52 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/07 21:52:21 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <stdlib.h> //for NULL
#include "main.h"
#include "libft.h"

int	is_match(char *str, t_file *file_list)
{
	return (match_star_pattern(str, file_list->name) \
	&& (is_hidden_file(str) || (!is_hidden_file(str) \
	&& file_list->name[0] != '.')));
}

char	*handle_ambiguous_error(char *target, t_file *head)
{
	char	*temp;

	temp = rm_escape_char(target);
	ft_eprintf("minishell: %s: ambiguous redirect\n", temp);
	free(temp);
	free_file_list(head);
	return (NULL);
}
