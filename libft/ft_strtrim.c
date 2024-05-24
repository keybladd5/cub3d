/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:24:01 by polmarti          #+#    #+#             */
/*   Updated: 2023/09/25 13:24:03 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*rtrn;
	int		last_i;

	if (!s1 || !set)
		return (0);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	last_i = ft_strlen(s1);
	while (last_i && ft_strchr(set, s1[last_i]))
		last_i--;
	rtrn = ft_substr(s1, 0, last_i + 1);
	if (!rtrn)
		return (0);
	return (rtrn);
}

/*char	*ft_strtrim_v1(char const *s1, char const *set)
{
	char	*rtrn;
	int		i;
	int		x;
	int		k;

	i = 0;
	x = ft_strlen(s1);
	k = 0;
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	while (x > i && ft_strchr(set, s1[x]))
		x--;
	rtrn = (char *)malloc(sizeof(char) * (x - i + 2));
	if (!rtrn)
		return (0);
	while (i <= x)
	{
		rtrn[k] = s1[i];
		i++;
		k++;
	}
	rtrn[k] = '\0';
	return (rtrn);
}*/
/*int	main()
{
	char s1[] = "1233Hola 13";
	printf("%s\n", ft_strtrim(s1, "123"));
	return(0);
}*/
