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
//si se llama a esta funcion con a en 0, 
//hace el color completamente trnasparente, 
//si se hace con 255, sin transparencia
int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	safe_pixel_put(mlx_image_t *image, int x, int y, int color)
{
	if (x < 0 || x >= WIDTH)
		return ;
	if (y < 0 || y >= HEIGHT)
		return ;
	mlx_put_pixel(image, x, y, color);
}

//if the flag is 0, select between east and west, else if south and north
mlx_texture_t	*get_texture_walls(t_data *d, int flag)
{
	if (flag == 0)
	{
		if (d->data_player.west == true)
			return (d->tex.we);
		else
			return (d->tex.ea);
	}
	else
	{
		if (d->data_player.south == true)
			return (d->tex.so);
		else
			return (d->tex.no);
	}
}

void	draw_wall_texture(t_data *d, int top_pix, int bottom_pix, double wall_h)
{
	double			x_o;
	double			y_o;
	mlx_texture_t	*texture;
	double			factor;

	texture = get_texture_walls(d, d->cast_rays.flag);
	d->tex.arr = (unsigned int *)texture->pixels;
	factor = (double)texture->height / wall_h;
	if (d->cast_rays.flag == 1)
		x_o = (uint32_t)fmodf((d->cast_rays.wall_hit_x_horizontal \
		* (texture->width / TILE_SIZE)), texture->width);
	else
		x_o = (uint32_t)fmodf((d->cast_rays.wall_hit_y_vertical \
		* (texture->width / TILE_SIZE)), texture->width);
	y_o = (top_pix - (HEIGHT >> 1) + (wall_h * 0.5)) * factor;
	if (y_o < 0)
		y_o = 0;
	while (top_pix < bottom_pix)
	{
		if ((uint32_t)y_o < texture->height && (uint32_t)x_o < texture->width)
			safe_pixel_put(d->image, d->cast_rays.index, top_pix, \
			reverse_bytes(d->tex.arr[(int)y_o * texture->width + (int)x_o]));
		y_o += factor;
		top_pix++;
	}
}

//first while 4 floor, the last 4 ceiling;
void	draw_floor_ceiling(t_data *d, int ray, int t_pix, int b_pix)
{
	int		i;

	i = b_pix;
	while (i < HEIGHT)
		safe_pixel_put(d->image, ray, i++, get_rgba(189, 181, 125, 255));
	i = 0;
	while (i < t_pix)
		safe_pixel_put(d->image, ray, i++, get_rgba(255, 255, 255, 255));
}
