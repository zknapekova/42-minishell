/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:11:50 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/04 20:00:23 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"
#include "env_vars.h"
#include "exec.h"
#include <stdlib.h> //for NULL
#include <errno.h>
// #define _BSD_SOURCE
#include <dirent.h> // for  opendir
#include "built_ins.h"

// globe_argv expands wildcards with *, the result is sorted, hidden files are not listed if the pattern is not of .* type
// the function frees the original argv and returns the new argv with globed arguments
char	**globe_argv(char **argv)
{
	t_file	*file_list;
	t_file	*head_file_list;
	char	**new_argv;
	int		i;
	t_bool	match_found;
	char	*new_arg;

	i = 1;
	if (!argv || !argv[0])
		return (NULL);
	new_argv = NULL;
	new_argv = append_str_to_array(new_argv, argv[0]);
	if (!new_argv)
		return (free_argv(argv), error_handler("Error in globe_argv"), NULL);
	while (argv[i])
	{
		// ft_printf("argv[i]: %s\n", argv[i]);
		if (ft_strchr(argv[i], '*') && is_in_cwd(argv[i]))
		{
			match_found = false;
			file_list = get_cwd_file_list();
			if (!file_list)
				break ;
			head_file_list = file_list;
			
			while (file_list)
			{
				if (match_star_pattern(argv[i], file_list->name) && (is_hidden_file(argv[i]) || (!is_hidden_file(argv[i]) && file_list->name[0] != '.')))
				{
					match_found = true;
					new_argv = append_str_to_array(new_argv, file_list->name);
					if (!new_argv)
						return (free_argv(argv), free_file_list(head_file_list), NULL);
				}
				file_list = file_list->next;
			}
			free_file_list(head_file_list);
			// if (match_found == false)
			// {
			// 	new_arg = rm_escape_char(argv[i]);
			// 	if (!new_arg)
			// 		return (free_argv(argv), NULL);
			// 	new_argv = append_str_to_array(new_argv, new_arg);
			// 	free(new_arg);
			// 	if (!new_argv)
			// 		return (free_argv(argv), NULL);
			// }
		}
		// else
		// {
		// 	new_argv = append_str_to_array(new_argv, argv[i]);
		// 	if (!new_argv)
		// 		return (free_argv(argv), NULL);
		// }
		if (match_found == false)
		{
			new_arg = rm_escape_char(argv[i]);
			if (!new_arg)
				return (free_argv(argv), NULL);
			new_argv = append_str_to_array(new_argv, new_arg);
			free(new_arg);
			if (!new_argv)
				return (free_argv(argv), NULL);
		}
		i++;
	}
	return (free_argv(argv), new_argv);
}

char	*globe_redir_target(char *target)
{
	t_file	*file_list;
	t_file	*head_file_list;
	char	*new_target;
	int		match_count;
	
	if (!target)
		return (NULL);
	new_target = NULL;
	ft_printf("GLobe target called\n");
	match_count = 0;
	if (ft_strchr(target, '*') && is_in_cwd(target))
	{
		ft_printf("Globbing\n");
		file_list = get_cwd_file_list();
		// if (!file_list)
		// 	break ;
		head_file_list = file_list;
		
		while (file_list)
		{
			// if (match_star_pattern(target, file_list->name) && (is_hidden_file(target) || (!is_hidden_file(target) && file_list->name[0] != '.')))
			if (file_list->d_type != DT_DIR && match_star_pattern(target, file_list->name) && (is_hidden_file(target) || (!is_hidden_file(target) && file_list->name[0] != '.')))
			{
				if (match_count >= 1)
				{
					ft_eprintf("minishell: %s: ambiguous redirect\n", rm_escape_char(target));
					return (free (target), NULL);
				}
				match_count++;
				new_target = ft_strdup(file_list->name);
			}
			file_list = file_list->next;
		}
		
	}
	if (match_count == 0)
	{
		new_target = ft_strdup(rm_escape_char(target));
		if (!new_target)
			return (error_handler("Error allocating new_target"), free(target), NULL);
	}
	return (free(target), new_target);
}

t_file	*get_cwd_file_list(void)
{
	char			cwd[1024];
	DIR				*dir;
	struct dirent	*sdirent;
	t_file			*file_list;

	if (getcwd(cwd, 1024) == NULL)
		return (error_handler("getcwd failed"), NULL);
	if (!dir_check(cwd))
		return (NULL);
	dir = opendir(cwd);
	sdirent = readdir(dir);
	file_list = NULL;
	while (sdirent)
	{
		file_list = append_file(file_list, sdirent->d_name, sdirent->d_type);
		sdirent = readdir(dir);
	}
	file_list = sort_file_list(file_list);
	return (closedir(dir), file_list);
}

t_file	*append_file(t_file *head, const char *name, unsigned char	d_type)
{
	t_file	*new;
	t_file	*cur;

	new = malloc(sizeof(t_file));
	if (!new)
		return (error_handler("malloc failed in append_file"), NULL);
	new->name = ft_strdup(name);
	new->d_type = d_type;
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

int match_star_pattern(char *pattern, char *str)
{
	char	*star;
	char	*backup;

	star = NULL;
	backup = NULL;
	while (*str)
	{
		if (*pattern == '\\' && *(pattern + 1) == '*')
		{
			pattern += 2;
			if (*str != '*')
				return (0);
			str++;
		}
		else if (*pattern == '*')
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
			return (0);
	}
	while (*pattern == '*')
		pattern++;
	return (*pattern == '\0');
}

int	is_in_cwd(char *str)
{
	if (!ft_strchr(str, '/'))
		return (1);
	if (str[0] == '.' && str[1] == '/')
	{
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
	{
		new_arr[j] = arr[j];
		j++;
	}
	new_arr[i] = ft_strdup(str);
	if (!new_arr[i])
		return (error_handler("Error appending str to array"), \
		free(new_arr), NULL);
	new_arr[i + 1] = NULL;
	free(arr);
	return (new_arr);
}