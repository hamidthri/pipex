/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htaheri <htaheri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:55:49 by htaheri           #+#    #+#             */
/*   Updated: 2023/07/27 17:19:55 by htaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gets_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer)
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	line = (char *) gnl_calloc ((i + 2), sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (gnl_strchr (buffer, '\n'))
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*next_line(char *buffer, char *line)
{
	char	*next;
	int		len;
	int		i;

	i = 0;
	len = gnl_strlen(line);
	if (!buffer[len])
	{
		free (buffer);
		return (NULL);
	}
	next = (char *) gnl_calloc ((gnl_strlen(buffer) - len + 1), sizeof(char));
	if (!next)
		return (NULL);
	while (buffer[len])
		next[i++] = buffer[len++];
	free (buffer);
	return (next);
}

char	*join_temp(char *buffer, char *temp)
{
	char	*buf_tmp;

	buf_tmp = buffer;
	buffer = gnl_strjoin(buffer, temp);
	free(buf_tmp);
	return (buffer);
}

char	*fd_read(int fd, char *buffer)
{
	char	*temp;
	int		count;

	temp = (char *) gnl_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!temp)
		return (NULL);
	count = 1;
	while (count != 0)
	{
		count = read(fd, temp, BUFFER_SIZE);
		if (count == -1)
		{
			free(temp);
			free(buffer);
			return (NULL);
		}
		temp[count] = '\0';
		buffer = join_temp(buffer, temp);
		if (!check(buffer, temp))
			return (NULL);
		if (gnl_strchr(buffer, '\n'))
			break ;
	}
	free(temp);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char		*buffer;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
	{
		buffer = (char *) gnl_calloc(1, sizeof(char));
		if (!buffer)
			return (NULL);
	}
	buffer = fd_read(fd, buffer);
	if (!buffer)
	{
		buffer = NULL;
		return (NULL);
	}
	line = gets_line(buffer);
	buffer = next_line(buffer, line);
	return (line);
}
