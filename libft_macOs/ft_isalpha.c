/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 12:02:38 by polmarti          #+#    #+#             */
/*   Updated: 2023/09/13 12:02:51 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}
/*#include <libc.h>
#include <ctype.h>*/
/*int	main(void)
{
	printf("%d\n", ft_isalpha(255));
	printf("%d\n", isalpha(255));
	return (0);
}*/
