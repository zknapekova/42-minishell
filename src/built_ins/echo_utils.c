#include "libft.h"

void	normalize_n_flag(char **input)
{
	int	i;

	if (input && input[1])
	{
		if (input[1][0] == '-' && input[1][1] == 'n')
		{
			i = 2;
			while (input[1][i])
			{
				if (input[1][i] != 'n')
					return ;
				i++;
			}
			free(input[1]);
			input[1] = ft_strdup("-n");
		}
	}
}
