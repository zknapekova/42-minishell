/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:38:27 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/07/01 17:34:06 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"
#include "env_vars.h"
#include "exec.h"
#include <stdlib.h> //for NULL
#include <errno.h>
#include <dirent.h> // for  opendir
#include "built_ins.h"

t_file	*get_cwd_file_list(void)
{
	char			cwd[1024];
	DIR				*dir;
	struct dirent	*sdirent;
	t_file			*file_list;

	if (getcwd(cwd, 1024) == NULL)
		return (error_handler("getcwd failed"), NULL);
	if (dir_check(cwd, "") == EXIT_FAILURE)
		return (NULL);
	dir = opendir(cwd);
	sdirent = readdir(dir);
	file_list = NULL;
	while (sdirent)
	{
		file_list = append_file(file_list, sdirent->d_name);
		sdirent = readdir(dir);
	}
	file_list = sort_file_list(file_list);
	return (closedir(dir), file_list);
}

t_file	*append_file(t_file *head, const char *name)
{
	t_file	*new;
	t_file	*cur;

	new = malloc(sizeof(t_file));
	if (!new)
		return (error_handler("malloc failed in append_file"), NULL);
	new->name = ft_strdup(name);
	if (!new->name)
		return (free(new), \
		error_handler("ft_strdup failed in append_file"), NULL);
	new->next = NULL;
	if (!head)
		return (new);
	cur = head;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
	return (head);
}

void	free_file_list(t_file *head)
{
	t_file	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->name);
		free(tmp);
	}
}

char	**append_str_to_array(char **arr, char *str)
{
	int		i;
	int		j;
	char	**new_arr;

	if (!str || !str[0])
		return (arr);
	i = 0;
	while (arr && arr[i])
		i++;
	new_arr = malloc(sizeof(char *) * (i + 2));
	if (!new_arr)
		return (free_array(arr), NULL);
	j = 0;
	while (j < i)
	{
		new_arr[j] = ft_strdup(arr[j]);
		if (!new_arr[j])
		{
			new_arr[j] = NULL;
			free_array(new_arr);
			free_array(arr);
			return (error_handler("Error copying array"), NULL);
		}
		j++;
	}
	new_arr[i] = ft_strdup(str);
	if (!new_arr[i])
	{
		new_arr[i] = NULL;
		free_array(new_arr);
		free_array(arr);
		return (error_handler("Error appending str"), NULL);
	}
	new_arr[i + 1] = NULL;
	free_array(arr); // full cleanup: strings + pointer array
	return (new_arr);
}
