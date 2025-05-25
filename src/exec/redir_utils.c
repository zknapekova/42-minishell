/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:00:36 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/05/22 17:14:40 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include "libft.h"
#include "env_vars.h"
#include "exec.h"
#include "parser_utils.h" // for print_indent()
#include <stdlib.h> //for NULL

char	*get_redir_target_str(t_data *data, t_redir_target *target)
{
	char			*target_str;
	char			*tmp_str;

	target_str = NULL;
	if (!target)
		return (NULL);
	while (target && target->value)
	{
		if (get_first_ind(target->value, '$', 0) != -1 \
		&& target->quote_type != QUOTE_SINGLE)
			tmp_str = extend_env_value_nf(data, target->value);
		else
			tmp_str = ft_strdup(target->value);
		if (!tmp_str)
			return (free (target_str), \
			error_handler("Error getting target_str"), NULL);
		target_str = ft_strjoin_ed(target_str, tmp_str, ft_strlen(tmp_str));
		free (tmp_str);
		if (!target_str)
			return (error_handler("Error getting target_str"), NULL);
		target = target->next;
	}
	return (target_str);
}
