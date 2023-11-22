/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 23:14:42 by ymomen            #+#    #+#             */
/*   Updated: 2023/11/22 23:14:48 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
		if (s[i - 1] == '\n')
			break ;
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
