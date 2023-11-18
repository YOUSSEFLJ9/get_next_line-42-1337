/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 00:32:36 by ymomen            #+#    #+#             */
/*   Updated: 2023/11/19 00:07:03 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
# define BUFFER_SIZE 5
// #include "get_next_line.h"
size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}
void shift(char *buf, size_t endl)
{
	int i;

	i = 0;
	while (endl < BUFFER_SIZE)
	{
		buf[i] = buf [endl];
		i++;
		endl++;
	}
	while (i < endl)
		buf[i++] = 0;
}
static char	*alloc_totalen(char *line, char *buf, size_t *totlen)
{
	size_t	linel;
	size_t	bufl;
	char	*newstr;

	linel = 0;
	bufl = 0;
	*totlen = 0;
	if (!line && !buf)
		return (NULL);
	if (line)
		linel = ft_strlen(line);
	if (buf)
		bufl = ft_strlen(buf);
	*totlen = linel + bufl;
	newstr = (char *) malloc(*totlen + 1);
	if (!newstr)
		return (NULL);
	return (newstr);
}

char	*ft_strjoin(char *line, char *buf)
{
	size_t	i;
	size_t	count;
	char	*newstr;
	size_t	totlen;

	i = 0;
	count = 0;
	newstr = alloc_totalen(line, buf, &totlen);
	if (!newstr)
		return (NULL);
	while (line && line[count] && totlen > count)
	{
		newstr[count] = line[count];
		count++;
	}
	while (buf && buf[i] && totlen > (count + i))
	{
		newstr[count + i] = buf[i];
		i++;
		if(buf[i] == '\n')
		{
			newstr[count + i] = buf[i];
			i++;
			break ;
		}
			
	}
	newstr[count + i] = '\0';

	 if (line != NULL)
		free(line);
	return (newstr);
}

size_t	ft_strchr( char *s, size_t readit)
{
	size_t	i;

	i = 1;
	while (s[i- 1] && readit >= i)
	{
		if (s[i-1] == '\n')
			return (i);
		i++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char		buf[BUFFER_SIZE + 1];
	size_t			readit;
	char			*line = NULL;
	size_t			endl;

	if (read(fd, buf, 0) == -1)
		return (NULL);
	readit = 1;
	endl = 0;
	if (*buf != 0)
	{
		line = ft_strjoin(line, buf);
	}
	while (endl == 0 && readit > 0)
	{
		
		readit = read(fd, buf, BUFFER_SIZE);
		if (readit <= 0)
			return (0);
		endl = ft_strchr(buf, readit);	
		line = ft_strjoin(line, buf);
		if(endl != 0)
			shift(buf, endl);
	}
	return (line);
}

int main()
{
	int file = open("test.txt", O_RDONLY, 0777);
	int i = 100;
	if(file == -1)
		return (0);
	while(i--)
		printf("%s" ,get_next_line(file));
}
