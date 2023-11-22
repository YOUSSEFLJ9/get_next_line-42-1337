/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 00:32:36 by ymomen            #+#    #+#             */
/*   Updated: 2023/11/22 14:45:33 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line(char *buf, int fd, char *line )
{
	int	readit;
	int	endl;

	readit = 1;
	endl = -1337;
	while (endl == -1337 && readit > 0)
	{
		readit = read(fd, buf, BUFFER_SIZE);
		buf[readit] = '\0';
		if (readit == 0)
			return (shift(buf, BUFFER_SIZE), line);
		endl = ft_strchr(buf, readit);
		line = ft_strjoin(line, buf);
		if (!line)
			return (NULL);
		if (endl >= 0)
			shift(buf, endl);
	}
	return (line);
}
char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	int			endl;

	line = NULL;
	endl = -1337;
	if (read(fd, buf, 0) == -1)
		return (shift(buf, BUFFER_SIZE), NULL);
	if (*buf != 0)
	{
		line = ft_strjoin(line, buf);
		if (!line)
			return (NULL);
		if (0 > (endl = ft_strchr(buf, BUFFER_SIZE)))
			shift(buf, BUFFER_SIZE);
		else
			return (shift(buf, endl), line);
	}
	return (get_line(buf, fd, line));
}
