/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 11:14:59 by polmarti          #+#    #+#             */
/*   Updated: 2023/07/20 17:39:09 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (str1[i] || str2[i]))
	{
		if ((unsigned char)str1[i] == (unsigned char)str2[i])
			i++;
		else
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	}
	return (0);
}
/*#include <stdio.h>
#include <string.h>
int main (void)
{
	char	str1[] = "asdasdasdasdasdasdasdasd";
	char	str2[] = "asdasdasdasdasdasdasdasd";
	printf("%i\n", ft_strncmp(str1, str2, 24));
	printf("%i", strncmp(str1, str2, 1));
	return (0);
}*/
