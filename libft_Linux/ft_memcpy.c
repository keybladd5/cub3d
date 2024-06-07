/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 20:13:09 by polmarti          #+#    #+#             */
/*   Updated: 2023/09/13 20:13:13 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)dest;
	if (!dest && !src)
		return (dest);
	while (n-- > 0)
	{
		*ptr++ = *(unsigned char *)src;
		src++;
	}
	return (dest);
}
/*#include <string.h>
#include <stdio.h>
int	main()
{
	char	p[20];
	char	l[20];
	char	j[4] = "Hola";
	char	x[4] = "Hola";

	printf("%s\n", ft_memcpy(l, j, 4));
	printf("%s\n", memcpy(p, x, 4));
	return (0);
}*/