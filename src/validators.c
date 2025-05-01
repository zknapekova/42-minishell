
#include "../libft/libft.h"
#include "../include/env_vars.h"
#include <stdlib.h>

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