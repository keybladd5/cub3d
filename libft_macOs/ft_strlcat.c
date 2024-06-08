/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 11:16:17 by polmarti          #+#    #+#             */
/*   Updated: 2023/07/19 16:24:35 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	i;
	size_t	x;
	size_t	destlen;
	size_t	srclen;

	i = 0;
	destlen = ft_strlen(dest);
	srclen = ft_strlen(src);
	x = destlen;
	while (src[i] && x < (size - 1) && size > 0)
	{
		dest[x] = src[i];
		i++;
		x++;
	}
	if (!(dest[x] == '\0'))
		dest[x] = '\0';
	if (size < destlen)
		destlen = size;
	return (destlen + srclen);
}
//#include <stdio.h>
/*int main(void)
{

	char *dest;
    dest[0] = '\0';
    dest[11] = 'a';
	printf("%zu\n", ft_strlcat("pqrstuvwxyz", "", 0));
    printf("%zu\n", ft_strlcat(dest, "lorem ipsum", 15));
   return 0;
}*/