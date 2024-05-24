/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:45:43 by polmarti          #+#    #+#             */
/*   Updated: 2023/09/25 11:45:45 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*rtrn;
	size_t	i;

	i = ft_strlen(s1);
	if (!s1 || !s2)
		return (0);
	rtrn = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) +1));
	if (!rtrn)
		return (0);
	rtrn = ft_memcpy(rtrn, s1, (int)i);
	while (*s2)
	{
		rtrn[i] = *(char *)s2;
		i++;
		s2++;
	}
	rtrn[i] = '\0';
	return (rtrn);
}

/*int	main()
{
	char	s1[] = "lorem ipsum";
	char	s2[] = "dolor sit amet";
	char	*s = ft_strjoin(s1, s2);
	printf("%s\n", s);
	return (0);
}*/

//error si el s1 esta vacio
//error si el s2 estas vacio
// error en reservar memoria si estan vacios alguno de ellos