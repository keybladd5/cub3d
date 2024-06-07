/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 20:00:44 by polmarti          #+#    #+#             */
/*   Updated: 2023/09/17 20:00:47 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

/*#include <string.h>
#include <stdio.h>
int	main()
{
	printf("%d\n", ft_memcmp("abcdefghij", "abcdefgxyz", 8));
	printf("%d\n", memcmp("abcdefghij", "abcdefgxyz", 8));
}*/

//retorn en unsigned char a asegurar que los valores sean tratados 
//como números sin signo. 
