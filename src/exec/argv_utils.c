/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:55:18 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/06/07 22:08:57 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"
#include "env_vars.h"
#include "exec.h"
#include "parser_utils.h" // for print_indent()
#include <stdlib.h> //for NULL

char	*get_tmp_str(t_data *data, t_arg **args);

char	**get_argv(t_data *data, t_arg *args)
{
	char	**argv;
	char	*arg_str;
	int		list_len;
	int		i;
	t_arg	*args_copy;

	args_copy = args;
	list_len = get_list_len(args_copy);
	if (list_len <= 0)
		return (error_handler("Error: empty command"), NULL);
	argv = malloc(sizeof(char *) * (list_len + 1));
	if (!argv)
		return (error_handler("failed to allocate argv list"), NULL);
	i = 0;
	while (i < list_len)
	{
		arg_str = get_arg_str(data, &args_copy);
		if (!arg_str)
			return (free_argv(argv), NULL);
		argv[i] = arg_str;
		i++;
	}
	argv[i] = NULL;
	argv = globe_argv(argv);
	return (argv);
}

char	*get_arg_str(t_data *data, t_arg **args)
{
	char	*arg_str;
	char	*tmp_str;

	arg_str = NULL;
	while ((*args)->value)
	{
		tmp_str = get_tmp_str(data, args);
		if (!tmp_str)
			return (error_handler("Error getting arg_str"), NULL);
		arg_str = ft_strjoin_ed(arg_str, tmp_str, ft_strlen(tmp_str));
		free (tmp_str);
		if (!arg_str)
			return (error_handler("Error getting arg_str"), NULL);
		if ((*args)->word_join == W_SPLIT)
		{
			(*args) = (*args)->next;
			break ;
		}
		(*args) = (*args)->next;
	}
	return (arg_str);
}

char	*get_tmp_str(t_data *data, t_arg **args)
{
	char	*tmp_str;

	if (get_first_ind((*args)->value, '$', 0) != -1 \
		&& (*args)->quote_type != QUOTE_SINGLE)
		tmp_str = extend_env_value_nf(data, (*args)->value);
	else if ((*args)->quote_type != QUOTE_NONE)
		tmp_str = escape_wildcard((*args)->value);
	else
		tmp_str = ft_strdup((*args)->value);
	return (tmp_str);
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
	if (!argv)
		return ;
	while (argv[i])
	{
		free (argv[i]);
		i++;
	}
	free (argv);
}
