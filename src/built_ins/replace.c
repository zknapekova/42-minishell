/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 23:35:47 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/07/08 23:35:54 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"
#include "env_vars.h"
#include "exec.h"

char	*replace_str(char *str, t_data *data, char *key, int i)
{
	t_env_node	*node;
	char		*temp_str;
	char		*pre_str;
	char		*post_str;

	node = search_env_list(data, key);
	if (!node)
		return (ft_eprintf("env var %s not set\n", key), NULL);
	pre_str = ft_substr(str, 0, i);
	if (!pre_str)
		return (error_handler("malloc error"), NULL);
	temp_str = ft_strjoin(pre_str, node->value);
	if (!temp_str)
		return (free(pre_str), error_handler("malloc error"), NULL);
	free(pre_str);
	pre_str = NULL;
	post_str = ft_substr(str, i + ft_strlen(key) + 1, ft_strlen(str) - (i + 1));
	if (!post_str)
		return (error_handler("malloc error"), NULL);
	pre_str = ft_strjoin(temp_str, post_str);
	if (!pre_str)
		return (error_handler("malloc error"), \
		free(post_str), free(temp_str), NULL);
	return (free(post_str), free(temp_str), pre_str);
}

char	*replace_special_parameter(char *str, t_data *data)
{
	int			i;
	char		*post_str;
	char		*replaced_str;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			post_str = replace_str(str, data, "?", i);
			if (!post_str)
				return (error_handler("malloc error"), NULL);
			replaced_str = replace_special_parameter(post_str, data);
			return (replaced_str);
		}
	}
	return (str);
}

char	*replace_empty(char *str, t_data *data)
{
	int			i;
	char		*post_str;
	char		*replaced_str;
	int			len;

	i = 0;
	len = ft_strlen(str);
	while (len >= 6 + i)
	{
		if (str[i] == '$' && str[i + 1] == 'E' && str[i + 2] == 'M' \
		&& str[i + 3] == 'P' && str[i + 4] == 'T' && str[i + 5] == 'Y')
		{
			post_str = replace_str(str, data, "EMPTY", i);
			if (!post_str)
				return (error_handler("malloc error"), NULL);
			replaced_str = replace_special_parameter(post_str, data);
			return (replaced_str);
		}
		i++;
	}
	return (str);
}
