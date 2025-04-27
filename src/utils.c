/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zuknapek <zuknapek@student.42prague.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:41:41 by zuknapek          #+#    #+#             */
/*   Updated: 2025/04/27 18:58:47 by zuknapek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

int	get_first_ind(char *str, char c, int start)
{
	int	i;

	i = start;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
	    i++;
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

int validate_env_var_name(char *key_value, int eq_ind)
{
    int 	i;
	char	*var_name;

    i = 0;
	var_name = ft_substr(key_value, 0, eq_ind);
    if (ft_isdigit(var_name[i]))
           return (free(var_name), 0);
    while (var_name[i])
    {
        if (!ft_isalnum(var_name[i]) && var_name[i] != '_' && var_name[i] != '$')
            return(free(var_name), 0);
        i++;
    }
    return (free(var_name), 1);
}