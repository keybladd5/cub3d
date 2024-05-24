/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 10:21:22 by polmarti          #+#    #+#             */
/*   Updated: 2023/10/05 13:58:33 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;

	if (!s)
		return (0);
	if (len > (ft_strlen(s) - (size_t)start))
		len = ft_strlen(s) - (size_t)start;
	if (start >= ft_strlen(s))
	{
		dst = ft_strdup("");
		if (!dst)
			return (0);
		return (dst);
	}
	dst = (char *)ft_calloc(sizeof(char), len + 1);
	if (!dst)
		return (0);
	dst = ft_memcpy(dst, s + start, len);
	return (dst);
}

/*#include <stdio.h>
#include <stdlib.h>
int	main()
{
	//char	str[] = "lorem ipsum dolor sit amet";
	char	*sub;
	//size_t size = 20;
	sub = ft_substr("hola", 4, 1);
	printf("%s\n", sub);
	free(sub);
	return (0);
}*/

// h o l a
/*comentarios
23 el string viene vacio?
25 CASO LIMITE OVERLAP 1 > (4-2) = 1 (empieza en la posicion 2 y copia 1 veces, 
pero el string desde la posicion solo puede copia 2 veces sin hacer overlap, 
entonces se reasigna en len para evitar el overlap)
28 start es mayor que el final o igual que el final del string? CASO LIMITE
29 RETORNO UN PUNTERO VACIO 
*/
