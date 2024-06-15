/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:39:48 by polmarti          #+#    #+#             */
/*   Updated: 2024/05/07 11:39:51 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void safe_pixel_put(mlx_image_t *image, int x, int y, int color)
{
	if (x < 0) // check the x position
		return ;
	else if (x >= WIDTH)
		return ;
	if (y < 0) // check the y position
		return ;
	else if (y >= HEIGHT)
		return ;
	mlx_put_pixel(image, x, y, color); // put the pixel
}

int main(int argc, char **argv)
{
	t_data	d;

	if (ft_parse_input(argc, argv, &d.map))
		return(EXIT_FAILURE);
	ft_free_map(&d.map);
	return (EXIT_SUCCESS);
}
