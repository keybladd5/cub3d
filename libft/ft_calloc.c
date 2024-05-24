/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:50:34 by polmarti          #+#    #+#             */
/*   Updated: 2023/09/20 10:50:36 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*rtr;

	rtr = (void *)malloc(count * size);
	if (rtr == NULL)
		return (NULL);
	ft_bzero(rtr, size * count);
	return (rtr);
}

/*int	main()
{
	int	i = 0;
	int	*arr = (int *)calloc(1, sizeof(int));
	int	*arr1 = (int *)ft_calloc(1, sizeof(int));
	while(i++<2)
		//printf("%d\n", arr[i]);
		printf("%p\n", arr1);
	free(arr);
	free(arr1);
	return (0); 
}*/