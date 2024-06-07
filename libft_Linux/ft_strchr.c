/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 21:17:15 by polmarti          #+#    #+#             */
/*   Updated: 2023/09/14 21:17:17 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*(char *)s && *(char *)s != (char)c)
		s++;
	if (*(char *)s != (char)c)
		return (0);
	return ((char *)s);
}

/*#include <stdio.h>
int	main(void)
{
	char	*ptr = "Hola que tal estas hoy?";
	printf("%s\n", ft_strchr(ptr, 'a'));
	return (0);
}*/