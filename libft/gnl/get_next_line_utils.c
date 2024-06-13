/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:07:54 by polmarti          #+#    #+#             */
/*   Updated: 2023/10/19 11:07:56 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr_s(const char *s, int c)
{
	while (*(char *)s && *(char *)s != (char)c)
		s++;
	if (*(char *)s != (char)c)
		return (0);
	return ((char *)s);
}

size_t	ft_strlen_s(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin_s(char *s1, char *s2)
{
	char	*rtrn;
	int		i;

	i = 0;
	if (!s2)
		return (0);
	rtrn = (char *)malloc(sizeof(char) * (ft_strlen_s(s1) + ft_strlen_s(s2)+1));
	if (!rtrn)
		return (free(s1), NULL);
	if (s1)
	{
		while (s1[i])
		{
			rtrn[i] = s1[i];
			i++;
		}
	}
	while (*s2)
		rtrn[i++] = *s2++;
	rtrn[i] = '\0';
	free(s1);
	return (rtrn);
}

char	*ft_substr_s(char *s, unsigned int start, size_t len)
{
	char	*dst;
	char	*tmp;
	int		x;

	if (!s)
		return (0);
	if (len > (ft_strlen_s(s) - (size_t)start))
		len = ft_strlen_s(s) - (size_t)start;
	if (start >= ft_strlen_s(s))
	{
		dst = (char *)malloc(sizeof(char));
		if (!dst)
			return (0);
		dst[0] = '\0';
		return (dst);
	}
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	tmp = dst;
	x = len;
	while (len--)
		*tmp++ = s[start++];
	dst[x] = '\0';
	return (dst);
}
