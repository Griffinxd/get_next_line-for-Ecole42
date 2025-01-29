/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanav <ymanav@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:45:05 by ymanav            #+#    #+#             */
/*   Updated: 2025/01/29 12:48:15 by ymanav           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

static char	*get_buffer(int fd, char *filepos)
{
	char	*buffer;
	int		bytesread;

	buffer = (char *)malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	bytesread = 1;
	while (!ft_findnl(filepos) && (bytesread != 0))
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread == -1)
		{
			free(filepos);
			free(buffer);
			return (NULL);
		}
		buffer[bytesread] = '\0';
		filepos = ft_strjoin(filepos, buffer);
	}
	free(buffer);
	return (filepos);
}

static char	*get_line(char *filepos)
{
	int		i;
	char	*line;

	if (!filepos[0])
		return (NULL);
	i = 0;
	while (filepos[i] != '\0' && filepos[i] != '\n')
		i++;
	if (ft_findnl(filepos))
		line = (char *)malloc(sizeof(char) * (i + 2));
	else
		line = (char *)malloc(sizeof(char) * (i + 1));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (filepos[i] != '\0' && filepos[i] != '\n')
	{
		line[i] = filepos[i];
		++i;
	}
	if (filepos[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*set_buffer(char *filepos)
{
	char	*rest;
	int		i;
	int		j;

	i = 0;
	while (filepos[i] != '\0' && filepos[i] != '\n')
		i++;
	if (!filepos[i])
	{
		free(filepos);
		return (NULL);
	}
	rest = (char *)malloc(sizeof(char) * (ft_strlen(filepos) - i + 1));
	if (rest == NULL)
		return (NULL);
	i++;
	j = 0;
	while (filepos[i] != '\0')
		rest[j++] = filepos[i++];
	rest[j] = '\0';
	free(filepos);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*filepos = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	filepos = get_buffer(fd, filepos);
	if (filepos == NULL)
		return (NULL);
	line = get_line(filepos);
	if (line == NULL)
	{
		free(filepos);
		filepos = NULL;
		return (NULL);
	}
	filepos = set_buffer(filepos);
	return (line);
}
