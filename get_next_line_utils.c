/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 00:32:39 by ymomen            #+#    #+#             */
/*   Updated: 2023/11/18 17:39:24 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

static char	*alloc_totalen(char *s1, char *s2, size_t *totlen)
{
	size_t	s1l;
	size_t	s2l;
	char	*newstr;

	s1l = 0;
	s2l = 0;
	*totlen = 0;
	if (!s1 && !s2)
		return (NULL);
	if (s1)
		s1l = ft_strlen(s1);
	if (s2)
		s2l = ft_strlen(s2);
	*totlen = s1l + s2l;
	newstr = (char *) malloc(totlen + 1);
	if (!newstr)
		return (NULL);
	return (newstr);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	count;
	char	*newstr;
	size_t	totlen;

	i = 0;
	count = 0;
	newstr = alloc_totalen(s1, s2, &totlen);
	while (s1[count] && totlen > count)
	{
		newstr[count] = s1[count];
		count++;
	}
	while (s2[i] && totlen > (count + i))
	{
		newstr[count + i] = s2[i];
		i++;
	}
	newstr[count + i] = '\0';
	free(s1);
	free(s2);
	return (newstr);
}

size_t	ft_strchr( char *s, size_t readit)
{
	size_t	i;

	i = 0;
	while (s[i] && readit > i)
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}
