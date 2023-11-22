/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:46:53 by ymomen            #+#    #+#             */
/*   Updated: 2023/11/22 17:42:20 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H 
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE  10000000
# endif
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

/* FUNCTIONS */
char	*read_and_getline(char *buf, int fd, char *line);
void	free_it(char *str);
char	*ft_strjoin(char *line, char *buf);
void	shift(char *buf, int endl);
int		ft_strlen(char *s);
int		ft_strchr( char *s, int readit);
char	*get_next_line(int fd);
#endif

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

void	shift(char *buf, int endl)
{
	int	i;

	i = 0;
	while (endl < BUFFER_SIZE && buf[endl])
		buf[i++] = buf [endl++];
	while (i < endl)
		buf[i++] = 0;
}

static char	*alloc_totalen(char *line, char *buf, int *totlen)
{
	int		line_len;
	int		buf_len;
	char	*newstr;

	line_len = 0;
	buf_len = 0;
	*totlen = 0;
	if (!line && !buf)
		return (NULL);
	if (line)
		line_len = ft_strlen(line);
	buf_len = ft_strlen(buf);
	*totlen = line_len + buf_len;
	newstr = (char *) malloc(*totlen + 1);
	if (!newstr)
		return (NULL);
	return (newstr);
}

char	*ft_strjoin(char *line, char *buf)
{
	int		i;
	int		count;
	char	*newstr;
	int		totlen;

	i = 0;
	count = 0;
	newstr = alloc_totalen(line, buf, &totlen);
	if (!newstr)
		return (free_it(line), NULL);
	while (line && line[count] && totlen > count)
	{
		newstr[count] = line[count];
		count++;
	}
	free_it(line);
	while (buf[i] && totlen > count)
	{
		newstr[count++] = buf[i++];
		if (buf[i - 1] == '\n')
			break ;
	}
	newstr[count] = '\0';
	return (newstr);
}
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

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	int			endl;

	line = NULL;
	endl = 0;
	if (read(fd, buf, 0) == -1)
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

int	main(void)
{
	char	*line;
	int		file;

	int i = 2;

	file = open("giant_line.txt", O_RDONLY);
	if (file == -1)
		return (0);
	while(i)
	{
		printf("%s", get_next_line(file));
		i--;
	}
}
