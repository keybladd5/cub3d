/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 10:51:39 by polmarti          #+#    #+#             */
/*   Updated: 2023/09/26 10:51:41 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*rtrn;
	int				len;
	unsigned int	i;

	i = 0;
	len = ft_strlen(s);
	if (!s || !f)
		return (0);
	rtrn = (char *)ft_calloc(sizeof(char), len +1);
	if (!rtrn)
		return (0);
	while (s[i])
	{
		rtrn[i] = f(i, s[i]);
		i++;
	}
	return (rtrn);
}

/*char	ft_f(unsigned int c, char p)
{
	if (p >= 65 && p <= 90)
		p = p + 32;
	c = p;
	return (c);
}

int main()
{
	char	*s = "HOLA";
	s = ft_strmapi(s, ft_f);
	printf("%s\n", s);
	return (0);
}*/