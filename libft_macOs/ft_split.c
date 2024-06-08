/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 10:41:44 by polmarti          #+#    #+#             */
/*   Updated: 2023/09/28 10:41:46 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cnt_str(const char *s, char c)
{
	int	cnt;
	int	newword;

	newword = 1;
	cnt = 0;
	while (*s)
	{
		if (*s != c && newword == 1)
		{
			cnt++;
			newword = 0;
		}
		else if (*s == c)
			newword = 1;
		s++;
	}
	return (cnt);
}

static void	*ft_free(char **ptr, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	*p;
	char	**rtrn;
	size_t	cnt;
	size_t	len;

	cnt = ft_cnt_str(s, c);
	len = 0;
	rtrn = malloc(sizeof(char *) * (cnt +1));
	if (!rtrn)
		return (0);
	while (len < cnt)
	{
		while (*s == c && *s)
			s++;
		p = (char *)s;
		while (*s != c && *s)
			s++;
		rtrn[len] = ft_substr(p, 0, s - p);
		if (!rtrn[len])
			return (ft_free(rtrn, len));
		len++;
	}
	rtrn[len] = NULL;
	return (rtrn);
}

/*int	main()
{
	const char 	*p = "\0aa\0bbb";
	char		**pp;
	int			i;

	i = 0;
	pp = ft_split(p, '\0');
	while(pp[i])
	{
		printf("%s\n", pp[i]);
		i++;
	}
	return (0);
}*/

//66por si la ocurrencia es en el primer caso y en la
// siguientes vueltas del bucle
//68almacenamos la primera posicion despues de la 'c' si 
//la hay previamente
//69recorremos el ptr original hasta la siguiente 'c'
//71p = s[0] original , s - p = la posicion del indice de 
//la siguiente 'c' 
//menos el valor de 'p' por si hubiera una posible 
//ocurrencia en primer lugar