#include "libft.h"
#include "main.h"

char	*rm_escape_char(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	if (!str || !str[0])
		return (NULL);
	new_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new_str)
		return (error_handler("Error allocating new str in rm_escape_char"), NULL);
	while (str[i])
	{
		if (str[i] == '\\')
			i++;
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

int	is_hidden_file(char *str)
{
	return (str[0] == '.');
}