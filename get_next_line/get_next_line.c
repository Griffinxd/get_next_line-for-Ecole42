/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanav <ymanav@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:45:05 by ymanav            #+#    #+#             */
/*   Updated: 2025/01/28 17:31:08 by ymanav           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	replace_old(char *buff, char **newbuff)
{
	*newbuff = buff;
	free(buff);
}

static char	*get_buffer(int fd, char *buffer)
{
	char	*temp;
	char	*newbuffer;
	int		bytesread;

	temp = (char *)malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (temp == NULL)
		return (NULL);
	bytesread = 1;
	while (!ft_strchr(buffer, '\n') && (bytesread != 0))
	{
		bytesread = read(fd, temp, BUFFER_SIZE);
		if (bytesread == -1)
		{
			freetwo(temp, buffer);
			return (NULL);
		}
		temp[bytesread] = '\0';
		if (buffer == NULL)
			newbuffer = ft_strdup(temp);
		else
			newbuffer = ft_strjoin(buffer, temp);
		replace_old(buffer, &newbuffer);
	}
	free(temp);
	return (buffer);
}

static char	*get_line(const char *buffer)
{
	int		i;
	char	*line;

	if (!buffer[0])
		return (NULL);
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		++i;
	}
	if (buffer[i] == '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*set_buffer(char *buffer)
{
	char	*rest;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	rest = (char *)malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (rest == NULL)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i] != '\0')
		rest[j++] = buffer[i++];
	rest[j] = '\0';
	free(buffer);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*buffer = "";
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = get_buffer(fd, buffer);
	if (buffer == NULL)
		return (NULL);
	line = get_line(buffer);
	if (line == NULL)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = set_buffer(buffer);
	return (line);
}
