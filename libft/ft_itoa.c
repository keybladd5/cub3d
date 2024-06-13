/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 10:51:22 by polmarti          #+#    #+#             */
/*   Updated: 2023/09/26 10:51:25 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n, int len)
{
	if (n < 0)
	{
		n = n * -1;
		len++;
		return (ft_intlen(n / 10, len + 1));
	}
	if (n > 0)
		return (ft_intlen(n / 10, len + 1));
	else
		return (len);
}

static char	*ft_itoa_supp(int n)
{
	char	*rtrn;
	int		i;
	int		x;

	i = 0;
	x = ft_intlen(n, 0);
	rtrn = (char *)malloc(sizeof(char) * x +1);
	if (!rtrn)
		return (0);
	if (n < 0)
	{
		rtrn[0] = '-';
		n = n * -1;
		i++;
	}
	while (n > 0)
	{
		rtrn[--x] = (n % 10) + '0';
		n = n / 10;
		i++;
	}
	rtrn[i] = '\0';
	return (rtrn);
}

char	*ft_itoa(int n)
{
	char	*rtrn;

	if (n == -2147483648)
	{
		rtrn = ft_strdup("-2147483648");
		if (!rtrn)
			return (0);
	}
	else if (n == 0)
	{
		rtrn = ft_strdup("0");
		if (!rtrn)
			return (0);
	}
	else
	{
		rtrn = ft_itoa_supp(n);
		if (!rtrn)
			return (0);
	}
	return (rtrn);
}

/*int	main()
{
	printf("La longitud de n es: %d\n", ft_intlen(-2147483647, 0));
	printf("N pasado a un string es: %s \n", ft_itoa(-2147483648));
	return (0);
}*/
