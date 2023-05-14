/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ychihab <ychihab@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:13:06 by ychihab           #+#    #+#             */
/*   Updated: 2022/12/19 13:25:26 by ychihab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_line(char *superline)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	if (!superline[0])
		return (NULL);
	while (superline[i] != '\n' && superline[i])
		i++;
	if (superline[i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	while (j < i)
	{
		line[j] = superline[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*rest_buffer(char *superline)
{
	int		len;
	int		i;
	char	*buffer;

	i = 0;
	if (superline[i] == '\0')
	{
		free(superline);
		return (NULL);
	}
	while (superline[i] && superline[i] != '\n')
		i++;
	if (superline[i] == '\n')
		i++;
	buffer = malloc(ft_strlen(superline) - i + 1);
	if (!buffer)
		return (NULL);
	len = 0;
	while (superline[i])
		buffer[len++] = superline[i++];
	buffer[len] = '\0';
	free (superline);
	return (buffer);
}

char	*get_read(int fd, char *ptr)
{
	char	*buffer;
	int		n;

	n = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (n != 0 && !ft_strchr(ptr, '\n'))
	{
		n = read(fd, buffer, BUFFER_SIZE);
		if (n == -1)
		{
			free (buffer);
			free(ptr);
			return (NULL);
		}
		buffer[n] = '\0';
		ptr = ft_strjoin(ptr, buffer);
	}
	free (buffer);
	return (ptr);
}

char	*get_next_line(int fd)
{
	static char	*ptr;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ptr = get_read(fd, ptr);
	if (!ptr)
		return (NULL);
	line = ft_get_line(ptr);
	ptr = rest_buffer(ptr);
	return (line);
}
