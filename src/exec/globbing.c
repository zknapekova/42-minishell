/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:11:50 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/02 20:06:16 by jgrigorj         ###   ########.fr       */
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

// globing should be done while removing quotes, not after!
char	**globe_argv(char **argv)
{
	t_file	*file_list;
	t_file	*head_file_list;
	char	**new_argv;
	int	i;
	
	i = 1;
	new_argv = NULL;
	new_argv = append_str_to_array(new_argv, argv[0]);
	if (!new_argv)
		return (free_argv(argv), error_handler("Error in globe_argv"), NULL);
	while (argv[i])
	{
		if (ft_strchr(argv[i], '*') && is_in_cwd(argv[i]))
		{
			file_list = get_cwd_file_list();
			if (!file_list)
				break;
			head_file_list = file_list;
			while (file_list)
			{
				if (match_star_pattern(argv[i], file_list->name))
				{
					new_argv = append_str_to_array(new_argv, file_list->name);
					if (!new_argv)
						return (free_argv(argv), free_file_list(head_file_list), NULL);
				}
				file_list = file_list->next;
			}
			free_file_list(head_file_list);
		}
		else
		{
			new_argv = append_str_to_array(new_argv, argv[i]);
			if (!new_argv)
				return (free_argv(argv), NULL);
		}
		
		i++;
	}
	return (free_argv(argv), new_argv);
}

// char	*globe_redir_target(char *redir_target)
// {
	
// }

t_file	*get_cwd_file_list(void)
{
	char	cwd[1024];
	DIR		*dir;
	struct  dirent *sdirent;
	t_file	*file_list;

	if (getcwd(cwd, 1024) == NULL)
		return (error_handler("getcwd failed"), NULL);
	if (!dir_check(cwd))
		return(NULL);
	dir = opendir(cwd);
	sdirent = readdir(dir);
	while (sdirent)
	{
		file_list = append_file(file_list, sdirent->d_name);
		sdirent = readdir(dir);
	}
	return (closedir(dir), file_list);
}

t_file	*append_file(t_file *head, const char *name)
{
	t_file *new;
	t_file *cur;

	new = malloc(sizeof(t_file));
	if (!new)
		return (error_handler("malloc failed in append_file"), NULL);
	new->name = ft_strdup(name);
	if (!new->name)
		return (free(new), error_handler("ft_strdup failed in append_file"), NULL);
	new->next = NULL;
	if (!head)
		return new;
	cur = head;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
	return head;
}

void	free_file_list(t_file *head)
{
	t_file *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->name);
		free(tmp);
	}
}

int match_star_pattern(char *pattern, char *str)
{
	const char *star;
	const char *backup;

	star  = NULL;
	backup  = NULL;
	while (*str)
	{
		if (*pattern == '*')
		{
			star = pattern++;
			backup = str;
		}
		else if (*pattern == *str)
		{
			pattern++;
			str++;
		}
		else if (star)
		{
			pattern = star + 1;
			str = ++backup;
		}
		else
			return 0;
	}
	while (*pattern == '*')
		pattern++;

	return (*pattern == '\0');
}

int	is_in_cwd(char *str)
{
	if (!ft_strchr(str, '/'))
		return (1);
	if (str[0] == '.' && str[1] == '/')	{
		if (!ft_strchr(str + 2, '/'))
			return (1);
		else
			return (0);
	}
	return (0);
}

char	**append_str_to_array(char **arr, char *str)
{
	int		i;
	int		j;
	char	**new_arr;

	i = 0;
	while (arr && arr[i])
		i++;
	new_arr = malloc(sizeof(char *) * (i + 2));
	if (!new_arr)
		return (NULL);
	j = 0;
	while (j < i)
		new_arr[j] = arr[j++];
	new_arr[i] = ft_strdup(str);
	if (!new_arr[i])
		return (error_handler("Error appending str to array"), free(new_arr), NULL);
	new_arr[i + 1] = NULL;
	free(arr);
	return (new_arr);
}