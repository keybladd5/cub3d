/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:46:14 by polmarti          #+#    #+#             */
/*   Updated: 2023/09/13 13:46:18 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if ((c >= 0 && c <= 127))
		return (1);
	return (0);
}
/*#include <libc.h>
#include <ctype.h>*/
/*int	main(void)
{
	printf("%d\n", ft_isascii(0));
	printf("%d\n", isascii(0));
	return (0);
}*/
