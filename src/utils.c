/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuknapek <zuknapek@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:41:41 by zuknapek          #+#    #+#             */
/*   Updated: 2025/04/12 17:44:13 by zuknapek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

int	get_first_occurr_index(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (i);
	}
	return (-1);
}

int get_first_occurr_non_alnum(char *str, int start)
{
    int i;

    i = start;
    while (str[i])
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (i);
        i++;
    }
    return (i);
}

int validate_env_var_name(char *var_name)
{
    int i;

    i = 0;
    if (ft_isdigit(var_name[i]))
           return (0);
    while (var_name[i])
    {
        if (!ft_isalnum(var_name[i]) && var_name[i] != '_')
            return(0);
        i++;
    }
    return (1);
}