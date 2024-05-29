/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:40:57 by polmarti          #+#    #+#             */
/*   Updated: 2024/05/27 11:41:03 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//funcion para obtener el color al llamar a put_pixel
//si se llama a esta funcion con a en 0, hace el color completamente trnasparente, si se hace con 255, sin transparencia
int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

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
int color_walls(t_data *d, int flag)
{
	d->cast_rays.ray_ngl = nor_angle(d->cast_rays.ray_ngl);
	if (flag == 0) //east and west
	{
		if (d->cast_rays.ray_ngl > M_PI / 2 && d->cast_rays.ray_ngl < 3 * (M_PI / 2))
			return (get_rgba(164, 13, 13, 175));// west wall
		else
			return  (get_rgba(120, 10, 10, 175));// east wall
	}
	else
	{
		if (d->cast_rays.ray_ngl > 0 && d->cast_rays.ray_ngl < M_PI)
			return (get_rgba(236, 36, 36, 175));// south wall
		else
			return (get_rgba(240, 105, 105, 175));// north wall
	}
}
void	draw_wall(t_data *d, int ray, int t_pix, int b_pix)	// draw the wall
{
	int color;

	color = color_walls(d, d->cast_rays.flag);
	while (t_pix < b_pix)
	{
		if(t_pix == 0 || t_pix == HEIGHT)
			safe_pixel_put(d->image, ray, t_pix++, get_rgba(0, 0, 0, 255));
		else
			safe_pixel_put(d->image, ray, t_pix++, color);
	}
}

void	draw_floor_ceiling(t_data *d, int ray, int t_pix, int b_pix)	// draw the floor and the ceiling
{
	int		i;

	i = b_pix;
	while (i < HEIGHT)
		safe_pixel_put(d->image, ray, i++, get_rgba(189, 181, 125, 125)); // floor
	i = 0;
	while (i < t_pix)
		safe_pixel_put(d->image, ray, i++, get_rgba(255, 255, 255, 125)); // ceiling
}