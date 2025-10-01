/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgrigorj <jgrigorj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:56:02 by jgrigorj          #+#    #+#             */
/*   Updated: 2025/01/11 16:27:16 by jgrigorj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <fcntl.h>

#include "libft.h"

char	*read_and_append(int fd, char *str, char *buffer)
{
	int	bytes_read;

	while (ft_strlen(buffer) < check_endline(buffer) && ft_strlen(buffer) > 0)
	{
		str = ft_strjoin_ed(str, buffer, ft_strlen(buffer));
		if (!str)
		{
			buffer[0] = '\0';
			return (NULL);
		}
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			buffer[0] = '\0';
			if (*str == '\0')
			{
				free((char *)str);
				return (NULL);
			}
			return (str);
		}
		buffer[bytes_read] = '\0';
	}
	return (str);
}

char	*buffer_to_rest(char *str, char *buffer)
{
	if (ft_strlen(buffer) && ft_strlen(buffer) >= check_endline(buffer))
	{
		str = ft_strjoin_ed(str, buffer, check_endline(buffer) + 1);
		if (!str)
		{
			buffer[0] = '\0';
			return (NULL);
		}
		ft_memmove(buffer, buffer + check_endline(buffer) + 1,
			ft_strlen(buffer) - check_endline(buffer));
	}
	return (str);
}

int	check_buffer(int fd, char *buffer)
{
	int	bytes_read;

	bytes_read = 0;
	if (!buffer[0])
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			return (-1);
		buffer[bytes_read] = '\0';
	}
	return (bytes_read);
}

// go get the new line!
char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	static int	last_fd;
	char		*str;

	if (fd != last_fd)
	{
		last_fd = fd;
		buffer[0] = '\0';
	}
	if (check_buffer(fd, buffer) < 0)
		return (NULL);
	str = (char *)malloc(1);
	if (!str)
	{
		buffer[0] = '\0';
		return (NULL);
	}
	str[0] = '\0';
	str = read_and_append(fd, str, buffer);
	str = buffer_to_rest(str, buffer);
	return (str);
}
