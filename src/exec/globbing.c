/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:11:50 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/07 20:02:48 by jgrigorj         ###   ########.fr       */
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

// globe_argv expands wildcards with *, the result is sorted, 
// hidden files are not listed if the pattern is not of .* type
// the function frees the original argv 
// and returns the new argv with globed arguments
char	**globe_argv(char **argv)
{
	char	**new_argv;
	int		i;
	t_bool	match_found;

	i = 1;
	if (!argv || !argv[0])
		return (NULL);
	new_argv = NULL;
	new_argv = append_str_to_array(new_argv, argv[0]);
	if (!new_argv)
		return (free_argv(argv), error_handler("Error in globe_argv"), NULL);
	while (argv[i])
	{
		match_found = false;
		new_argv = get_globbed_argv(new_argv, argv[i], &match_found);
		if (!new_argv)
			return (error_handler("Error globbing argv"), \
			free_argv(argv), NULL);
		new_argv = get_unglobbed_argv(new_argv, argv[i], match_found);
		if (!new_argv)
			return (error_handler("Error getting uglobbed argv"), \
			free_argv(argv), NULL);
		i++;
	}
	return (free_argv(argv), new_argv);
}

char	**get_globbed_argv(char **new_argv, char *argv, t_bool *match_found)
{
	t_file	*file_list;
	t_file	*head_file_list;

	if (ft_strchr(argv, '*') && is_in_cwd(argv) && !ft_strchr(argv, '='))
	{
		file_list = get_cwd_file_list();
		if (!file_list)
			return (free_argv(new_argv), NULL);
		head_file_list = file_list;
		while (file_list)
		{
			if (is_match(argv, file_list))
			{
				*match_found = true;
				new_argv = append_str_to_array(new_argv, file_list->name);
				if (!new_argv)
					return (free_file_list(head_file_list), NULL);
			}
			file_list = file_list->next;
		}
		free_file_list(head_file_list);
	}
	return (new_argv);
}

char	**get_unglobbed_argv(char **new_argv, char *argv, t_bool match_found)
{
	char	*new_arg;

	if (match_found == false)
	{
		if (!ft_strchr(argv, '='))
			new_arg = rm_escape_char(argv);
		else
			new_arg = ft_strdup(argv);
		if (!new_arg)
			return (free_argv(new_argv), NULL);
		new_argv = append_str_to_array(new_argv, new_arg);
		free(new_arg);
		if (!new_argv)
			return (NULL);
	}
	return (new_argv);
}

char	*globe_redir_target(char *target)
{
	char	*new_target;
	int		match_count;

	if (!target)
		return (NULL);
	new_target = NULL;
	match_count = 0;
	if (ft_strchr(target, '*') && is_in_cwd(target))
		new_target = get_globbed_target(target, &match_count);
	if (match_count == 0)
	{
		new_target = rm_escape_char(target);
		if (!new_target)
			return (error_handler("Error allocating new_target"), \
			free(target), NULL);
	}
	return (free(target), new_target);
}

char	*get_globbed_target(char *target, int *match_count)
{
	t_file	*file_list;
	t_file	*head_file_list;
	char	*new_target;

	new_target = NULL;
	file_list = get_cwd_file_list();
	head_file_list = file_list;
	while (file_list)
	{
		if (is_match(target, file_list))
		{
			free (new_target);
			if (*match_count >= 1)
				return (handle_ambiguous_error(target, head_file_list), NULL);
			(*match_count)++;
			new_target = ft_strdup(file_list->name);
			if (!new_target)
				return (error_handler("Error copying target"), \
				free_file_list(head_file_list), NULL);
		}
		file_list = file_list->next;
	}
	return (free_file_list(head_file_list), new_target);
}
