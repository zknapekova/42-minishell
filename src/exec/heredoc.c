#include "main.h"
#include "libft.h"
#include "env_vars.h"
#include "exec.h"
#include "parser_utils.h" // for print_indent()
#include <stdlib.h> //for NULL
#include <stdio.h> // for readline
#include <readline/readline.h>

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	if (s1 && !s2)
		return ((char *)s1);
	if (!s1 && s2)
	{
		s2_len = ft_strlen(s2);
		res = (char *)malloc(sizeof(char) * (s2_len + 1));
		if (!res)
			return (free(res), NULL);
		ft_strlcpy(res, s2, s2_len + 1);
		return (res);
	}
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	res = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!res)
		return (free((void *)s1), free(res), NULL);
	ft_strlcpy(res, s1, s1_len + 1);
	ft_strlcat(res, s2, s1_len + s2_len + 1);
	return (free((void *)s1), res);
}

int	ft_get_file_cont(char *lim, int fd)
{
	char	*line;
	//char	*file_cont;
	char	*limiter;

	line = NULL;
	//file_cont = NULL;
	limiter = ft_strjoin(lim, "\n");
	if (!limiter)
		return (error_handler("malloc failed"), 0);
	free(lim);
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			break ;
		if (!ft_strcmp(limiter, line))
			break ;
		if (write(fd, line, ft_strlen(line)) == -1)
			return (free(line), free(limiter), 0);;
		//file_cont = ft_strjoin_gnl(file_cont, line);
		/*if (!file_cont)
			return (free(line), free(limiter), 0);*/
		free(line);
	}
	free(line);
	free(limiter);
	return (1);
}
