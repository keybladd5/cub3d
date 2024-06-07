/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 20:05:15 by polmarti          #+#    #+#             */
/*   Updated: 2023/09/13 20:06:36 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	char p[20] = "hola que tal";
	char x[20] = "hola que tal";
	ft_bzero(x, 'p', 20);
	printf("%s\n", x);
	bzero(p, 'p', 20);
	printf("%s\n", p);
	return (0);
}*/