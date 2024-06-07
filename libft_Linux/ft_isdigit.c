/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isdigit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:29:28 by polmarti          #+#    #+#             */
/*   Updated: 2023/09/13 12:29:33 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}
/*#include <libc.h>
#include <ctype.h>*/
/*int	main(void)
{
	printf("%d\n", ft_isdigit(48));
	printf("%d\n", isdigit(48));
	return (0);
}*/