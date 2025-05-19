/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 17:29:44 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/05/19 20:43:28 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"
#include "env_vars.h"
#include <stdlib.h> //for NULL

int		get_list_len(t_arg *args);
char	*get_arg_str(t_data *data, t_arg *args);
void	free_argv(char **argv);

char	**get_arg_list(t_data *data, t_arg *args)
{
	char	**argv;
	char	*arg_str;
	int		list_len;
	int		i;
	t_arg	*args_copy;
	
	list_len = get_list_len(args_copy);
	if (list_len <= 0)
		return (error_handler("Error: empty command"), NULL);
	// 
	ft_printf("list_len: %d\n", list_len);
	argv = malloc(sizeof(char *) * (list_len + 1));
	if (!argv)
		return (error_handler("failed to allocate argv list"), NULL);
	i = 0;
	while (i <= list_len)
	{
		argv[i] = NULL;
		arg_str = get_arg_str(data, args_copy);
		if (!arg_str)
			return (free_argv(argv), NULL);
		argv[i] = ft_strdup(arg_str);
		if (!argv[i])
			return (free_argv(argv), error_handler("failed to copy argv"), NULL);
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

char	*get_arg_str(t_data *data, t_arg *args)
{
	char	*arg_str;
	char	*tmp_str;

	arg_str = NULL;
	while (args->value)
	{
		if (get_first_ind(args->value, '$', 0) != 0)
			tmp_str = extend_env_value_nf(data, args->value);
		else
			tmp_str = ft_strdup(args->value);
		if (!tmp_str)
			return (error_handler("Error getting arg_str"), NULL);
		arg_str = ft_strjoin_ed(arg_str, tmp_str, ft_strlen(args->value));
		if (!arg_str)
			return (free (tmp_str), error_handler("Error getting arg_str"), NULL);
		free (tmp_str);
		if (args->word_join == W_SPLIT)
		{
			args = args->next;
			break;
		}
		args = args->next;
	}
	(void)args;
	return (error_handler("Error getting arg_str"), NULL);
}

int	get_list_len(t_arg *args)
{
	t_arg	*curr;
	int		len;

	len = 0;
	if (!args)
		return (0);
	curr = args;
	while (curr)
	{
		if (curr->word_join == W_SPLIT)
			len++;
		curr = curr->next;
	}
	return (len);
}

void	free_argv(char **argv)
{
	int	i;
	
	i = 0;
	if  (!argv)
		return;
	while (argv[i])
	{
		free (argv[i]);
		i++;
	}
	free (argv);
}