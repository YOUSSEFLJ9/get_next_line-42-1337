/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 11:46:53 by ymomen            #+#    #+#             */
/*   Updated: 2023/11/22 13:26:42 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE  1
#endif
# include <unistd.h>
#include <stdlib.h>

char	*get_line(char *buf, int fd, char *line );
void	shift(char *buf, int endl);
void	free_it(char *str);
int		ft_strchr( char *s, int readit);
char	*ft_strjoin(char *line, char *buf, int endl);
char	*get_next_line(int fd);
int		ft_strlen(char *s);


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
		line = ft_strjoin(line, buf, readit);
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
	endl = 0;
	if (*buf != 0)
	{
		line = ft_strjoin(line, buf, BUFFER_SIZE);
		if (!line)
			return (NULL);
		if (!(endl = ft_strchr(buf, BUFFER_SIZE)))
			shift(buf, BUFFER_SIZE);
		else
			return (shift(buf, endl), line);
	}
	if (read(fd, buf, 0) == -1)
		return (shift(buf, BUFFER_SIZE), NULL);
	return (get_line(buf, fd, line));
}
int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char	*alloc_totalen(char *line, char *buf, int *totlen)
{
	int	line_len;
	int	buf_len;
	char	*newstr;

	buf_len = 0;
	line_len = 0;
	if (!line && !buf)
		return (NULL);
	if (line)
		line_len = ft_strlen(line);
	if (buf)
		buf_len = ft_strlen(buf);
	*totlen = line_len + buf_len;
	newstr = (char *) malloc(*totlen + 1);
	if (!newstr)
		return (NULL);
	return (newstr);
}

char	*ft_strjoin(char *line, char *buf, int readit)
{
	int		i;
	int		count;
	char	*newstr;
	int		totlen;

	i = 0;
	count = 0;
	newstr = alloc_totalen(line, buf, &totlen);
	if (!newstr)
		return(shift(buf, BUFFER_SIZE),NULL);
	while (line && line[count] && totlen > count)
	{
		newstr[count] = line[count];
		count++;
	}
	while (buf[i] && totlen > (count + i))
	{
		newstr[count++] = buf[i++];
		if( ft_strchr(buf, readit) == i - 1)
			break ;
	}
	newstr[count] = '\0';
	free_it(line);
	return (newstr);
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
	return (-1337);
}
void free_it(char *str)
{
	if (str)
		free(str);
	str = NULL;
}

void	shift(char *buf, int endl)
{
	int	i;

	i = 0;
	endl++;
	while (endl < BUFFER_SIZE && buf[endl])
		buf[i++] = buf [endl++];
	while (i < endl)
		buf[i++] = 0;
}
int main()
{
	char *line;
	int file = open("read_error.txt", O_RDONLY);
	if(file == -1)
		return (0);
	printf("%s" ,get_next_line(file));
	printf("%s" ,get_next_line(file));
	printf("%s" ,get_next_line(file));
	 printf("%s" ,get_next_line(file));
	printf("%s" ,get_next_line(file));
}

