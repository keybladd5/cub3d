/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 19:13:57 by polmarti          #+#    #+#             */
/*   Updated: 2023/10/14 19:13:59 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_p(int c, int *cntchr)
{
	int	check;

	check = write(1, &c, 1);
	if (check != -1)
		(*cntchr)++;
	else
		*cntchr = -1;
}

void	ft_putstr_p(char *str, int *cntchr)
{
	if (!str)
	{
		ft_putstr_p("(null)", cntchr);
		return ;
	}
	while (*str)
	{
		ft_putchar_p(*str, cntchr);
		if (*cntchr == -1)
			return ;
		str++;
	}
}

void	ft_nbase(unsigned long nb, unsigned int base, int *cntchr, char *b)
{
	if (*cntchr == -1)
		return ;
	if (nb < base)
	{
		ft_putchar_p(b[nb], cntchr);
		if (*cntchr == -1)
			return ;
	}
	else
	{
		ft_nbase(nb / base, base, cntchr, b);
		ft_nbase(nb % base, base, cntchr, b);
	}
}

void	ft_putnbr_p(int nb, int *cntchr)
{
	if (*cntchr == -1)
		return ;
	if (nb == -2147483648)
		ft_putstr_p("-2147483648", cntchr);
	else if (nb < 0)
	{
		ft_putchar_p('-', cntchr);
		if (*cntchr == -1)
			return ;
		ft_putnbr_p(-nb, cntchr);
	}
	else if (nb < 10)
	{
		ft_putchar_p(nb + '0', cntchr);
		if (*cntchr == -1)
			return ;
	}
	else
	{
		ft_putnbr_p(nb / 10, cntchr);
		ft_putnbr_p(nb % 10, cntchr);
	}
}
