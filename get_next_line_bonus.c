/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:59:42 by ymomen            #+#    #+#             */
/*   Updated: 2023/11/22 23:13:06 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	free_it(char *str)
{
	if (str)
		free(str);
	str = NULL;
}

int	ft_strchr( char *s, int readit)
{
	int	i;

	i = 1;
	while (s[i - 1] || readit >= i)
	{
		if (s[i - 1] == '\n')
			return (i);
		i++;
	}
	return (0);
}

char	*read_and_getline(char *buf, int fd, char *line)
{
	int	readit;
	int	endl;

	readit = 1;
	endl = 0;
	while (endl == 0 && readit > 0)
	{
		readit = read(fd, buf, BUFFER_SIZE);
		buf[readit] = '\0';
		if (readit == 0)
			return (shift(buf, BUFFER_SIZE), line);
		endl = ft_strchr(buf, readit);
		line = ft_strjoin(line, buf);
		if (!line)
			return (NULL);
		if (endl)
			shift(buf, endl);
	}
	return (line);
}

char	*get_next_line_v1(int fd, char *buf)
{
	char		*line;
	int			endl;

	line = NULL;
	endl = 0;
	if ((read(fd, buf, 0) == -1))
		return (shift(buf, BUFFER_SIZE), NULL);
	if (*buf != 0)
	{
		line = ft_strjoin(line, buf);
		if (!line)
			return (NULL);
		endl = ft_strchr(buf, BUFFER_SIZE);
		if (!endl)
			shift(buf, BUFFER_SIZE);
		else
			return (shift(buf, endl), line);
	}
	return (read_and_getline(buf, fd, line));
}

char *get_next_line(int fd)
{
	static char	buf[OPEN_MAX][BUFFER_SIZE + 1];

	if (fd > OPEN_MAX || fd <= -1)
		return (NULL);
	return (get_next_line_v1(fd, buf[fd]));
}
