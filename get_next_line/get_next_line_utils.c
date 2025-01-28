/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymanav <ymanav@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:45:01 by ymanav            #+#    #+#             */
/*   Updated: 2025/01/28 17:28:30 by ymanav           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (*str != '\0')
	{
		if (*str == (unsigned char)c)
			return ((char *)str);
		str++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)str);
	return (NULL);
}

size_t	ft_strlen(const char *string)
{
	size_t	len;

	len = 0;
	while (*string++ != '\0')
		len++;
	return (len);
}

char	*ft_strdup(const char *s)
{
	size_t	size;
	size_t	i;
	char	*string;

	size = ft_strlen(s) + 1;
	string = malloc(size * sizeof(char));
	if (string == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		string[i] = s[i];
		i++;
	}
	return (string);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t		size;
	char		*string;
	size_t		i;
	size_t		j;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	string = (char *)malloc(size * sizeof(char));
	if (!string)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		string[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		string[i + j] = s2[j];
		j++;
	}
	string[i + j] = '\0';
	return (string);
}

void	freetwo(char *s1, char *s2)
{
	free(s1);
	free(s2);
}
