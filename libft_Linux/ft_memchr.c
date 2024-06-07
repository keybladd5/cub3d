/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 19:49:12 by polmarti          #+#    #+#             */
/*   Updated: 2023/09/17 19:49:15 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n-- > 0)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return ((void *)s);
		s++;
	}
	return (0);
}
/*#include <string.h>
#include <stdio.h>
int	main(void)
{
	//char	*ptr = "";
	char	ptr2[] = {0, 1, 2, 3, 4, 5};
	printf("%s\n", ft_memchr(ptr2, 0, 0));
	printf("%s\n", memchr(ptr2, 0, 0));
	return (0);
}*/