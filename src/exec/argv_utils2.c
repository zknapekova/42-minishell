/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 00:13:08 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/07/07 02:26:13 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main.h"
#include "exec.h"
#include <stdlib.h> //for NULL

char	*handle_empty_quotes(t_arg **args)
{
	if (!args)
		return (NULL);
	if ((*args)->value[0] == '\0' && (*args)->quote_type != QUOTE_NONE
		&& (*args)->word_join == W_SPLIT)
		return ((*args) = (*args)->next, ft_strdup("''"));
	else
		return (NULL);
}

t_bool	fill_argv_list(t_data *data, char **argv, t_arg **args, int *i)
{
	char	*arg_str;
	
	while (*args)
	{
		arg_str = handle_empty_quotes(args);
		if (arg_str)
		{
			argv[(*i)++] = arg_str;
			continue ;
		}
		arg_str = get_arg_str(data, args);
		if (!arg_str)
		{
			free_argv(argv);
			return (false);
		}
		argv[(*i)++] = arg_str;
	}
	return (true);
}
