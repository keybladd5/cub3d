/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:18:52 by polmarti          #+#    #+#             */
/*   Updated: 2023/07/24 20:21:23 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	output;
	int	sign;

	output = 0;
	sign = 1;
	while (*str && (ft_strchr("\n\t\v\f\r ", *str)) != NULL)
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		str++;
		sign = -1;
	}
	while (*str && (ft_strchr("0123456789", *str)) != NULL)
	{
		output = (output * 10) + (*str - '0');
		str++;
	}
	return (output * sign);
}
/*#include <unistd.h>
#include <stdio.h>
int main(int argc, char *argv[]) 
{
  if (argc == 1)
    write(1, "\n", 1);
  int result = ft_atoi(argv[1]);

  printf("%d\n", result);
  return (0);
}*/
