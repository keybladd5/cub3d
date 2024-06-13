/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:09:11 by polmarti          #+#    #+#             */
/*   Updated: 2023/10/19 11:09:13 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*ft_strchr_s(const char *s, int c);

size_t	ft_strlen_s(const char *s);

char	*ft_strjoin_s(char *s1, char *s2);

char	*ft_substr_s(char *s, unsigned int start, size_t len);

char	*get_next_line(int fd);

#endif
