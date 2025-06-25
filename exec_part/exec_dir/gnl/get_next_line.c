/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: korzecho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 13:46:21 by korzecho          #+#    #+#             */
/*   Updated: 2024/09/08 13:46:23 by korzecho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static char	*set_line(char *line);
static char	*read_line(int fd, char *buffer, char *left_l);
static char	*ft_strchr(char *s, int c);

char	*get_next_line(int fd)
{
	static char	*left_line;
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
	{
		free(buffer);
		free(left_line);
		buffer = NULL;
		left_line = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = read_line(fd, buffer, left_line);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	left_line = set_line(line);
	return (line);
}

static char	*set_line(char *line)
{
	ssize_t	i;
	char	*left_l;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == 0 || line[1] == 0)
		return (NULL);
	left_l = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*left_l == 0)
	{
		free(left_l);
		return (NULL);
	}
	line[i + 1] = 0;
	return (left_l);
}

static char	*read_line(int fd, char *buffer, char *left_l)
{
	ssize_t	bytes_read;
	char	*tmp;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free (left_l);
			return (NULL);
		}
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = 0;
		if (!left_l)
			left_l = ft_strdup("");
		tmp = left_l;
		left_l = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (left_l);
}

static char	*ft_strchr(char *s, int c)
{
	char	*ptr;
	char	sign;

	sign = (char)c;
	ptr = (char *)s;
	while (*ptr != sign && *ptr)
		ptr++;
	if (*ptr == sign)
		return (ptr);
	return (NULL);
}
