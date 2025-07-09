/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:55:18 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/07/09 02:54:57 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_vars.h"
#include "exec.h"
#include "libft.h"
#include "main.h"
#include "parser_utils.h" // for print_indent()
#include <stdlib.h>       //for NULL

char		*get_tmp_str(t_data *data, t_arg **args);
static void	replace_arg_value(t_arg **args, char *str);

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
	arg_str = handle_empty_quotes(&args_copy);
	i = 0;
	if (arg_str)
		argv[i++] = arg_str;
	if (!fill_argv_list(data, argv, &args_copy, &i))
		return (NULL);
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
		free(tmp_str);
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
	int		dollar_ind;
	int		tilde_ind;
	int		len;
	char	*tilde_replaced;

	tilde_ind = get_first_ind((*args)->value, '~', 0);
	if (tilde_ind > -1 && (*args)->quote_type == QUOTE_NONE \
	&& !ft_strchr((*args)->value, '='))
	{
		tilde_replaced = replace_tilde((*args)->value, tilde_ind);
		if (tilde_replaced)
			replace_arg_value(args, tilde_replaced);
	}
	dollar_ind = get_first_ind((*args)->value, '$', 0);
	len = ft_strlen((*args)->value);
	if (should_extend_env(dollar_ind, len, args))
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

static void	replace_arg_value(t_arg **args, char *str)
{
	free((*args)->value);
	(*args)->value = str;
}
