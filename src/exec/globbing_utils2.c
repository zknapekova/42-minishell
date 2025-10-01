/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:38:27 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/07/06 21:58:17 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_ins.h"
#include "env_vars.h"
#include "exec.h"
#include "libft.h"
#include "main.h"
#include <dirent.h> // for  opendir
#include <errno.h>
#include <stdlib.h> //for NULL

t_bool	handle_copy_error(int i, char ***new_arr, char ***arr, \
		char *error_msg);

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
		return (free(new), error_handler("ft_strdup failed in append_file"),
			NULL);
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
		if (handle_copy_error(j, &new_arr, &arr, "Error copying array"))
			return (NULL);
		j++;
	}
	new_arr[i] = ft_strdup(str);
	if (handle_copy_error(i, &new_arr, &arr, "Error appending str"))
		return (NULL);
	new_arr[i + 1] = NULL;
	return (free_array(arr), new_arr);
}

t_bool	handle_copy_error(int i, char ***new_arr, char ***arr,
		char *error_msg)
{
	if (!(*new_arr)[i])
	{
		(*new_arr)[i] = NULL;
		free_array(*new_arr);
		free_array(*arr);
		error_handler(error_msg);
		return (true);
	}
	else
		return (false);
}
