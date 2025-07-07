/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 19:38:52 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/07/07 02:26:32 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "libft.h"
#include "main.h"
#include <stdlib.h> //for NULL

int	is_match(char *str, t_file *file_list)
{
	return (match_star_pattern(str, file_list->name) && (is_hidden_file(str)
			|| (!is_hidden_file(str) && file_list->name[0] != '.')));
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

void	remove_empty_strings(char **array)
{
	int	read;
	int	write;

	if (!array)
		return ;
	read = 0;
	write = 0;
	while (array[read])
	{
		// if (read && !ft_strncmp(array[read], "''", 2))
		// {
		// 	free(array[read]);
		// 	array[write++] = ft_strdup("\0");
		// }
		if (array[read][0] != '\0')
			array[write++] = array[read];
		else
			free(array[read]);
		read++;
	}
	array[write] = NULL;
}
