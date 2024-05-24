/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:36:12 by polmarti          #+#    #+#             */
/*   Updated: 2023/09/06 17:36:14 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;

	dest = malloc((sizeof(char) * (ft_strlen(src)+1)));
	if (!dest)
		return (0);
	return (ft_memcpy(dest, src, (ft_strlen(src)+1)));
}

/*int	main(void)
{
	char *src = "";
	char *dest = ft_strdup(src);
	if (!dest)
		return (NULL);
	printf("%s\n", dest);
	printf("%s\n", ft_strdup(src));
	free (dest);
	return (0);
}*/