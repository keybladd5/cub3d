/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:58:44 by polmarti          #+#    #+#             */
/*   Updated: 2023/07/18 17:02:36 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	x;

	x = ft_strlen(src);
	i = 0;
	if (!dst && !src)
		return (x);
	if (size == 0)
		return (x);
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (x);
}

/*#include <stdio.h>
#include <string.h>
int    main (void)
{
  char dest[10] = " ";
  char src[5] = "Hola";
  printf("%u", ft_strlcpy(dest, src, 0));
  printf("%s\n", dest);
  //printf("%lu", strlcpy(dest, src, 0));
  //printf("%s\n", dest);
  return (0);
}*/
