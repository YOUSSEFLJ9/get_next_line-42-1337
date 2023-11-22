/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 00:32:33 by ymomen            #+#    #+#             */
/*   Updated: 2023/11/22 14:38:16 by ymomen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H 
# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE  42
# endif

/* FUNCTIONS */
char	*get_line(char *buf, int fd, char *line );
void	shift(char *buf, int endl);
void	free_it(char *str);
int		ft_strchr( char *s, int readit);
char	*ft_strjoin(char *line, char *buf);
char	*get_next_line(int fd);
int		ft_strlen(char *s);
#endif