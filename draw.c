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
mlx_texture_t *get_texture_walls(t_data *d, int flag)
{
	if (flag == 0) //east and west
	{
		if (d->data_player.west == true)
			return (d->tex.we);// west wall
		else
			return  (d->tex.ea);// east wall
	}
	else//south and north
	{
		if (d->data_player.south == true)
			return (d->tex.so);// south wall
		else
			return (d->tex.no);// north wall
	}
}
/*void	draw_wall(t_data *d, int ray, int t_pix, int b_pix)	// draw the wall
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
}*/
double	get_x_o(mlx_texture_t	*texture, t_data *d)
{
	double	x_o;

	if (d->cast_rays.flag == 1)
		x_o = (int)fmodf((d->cast_rays.wall_hit_x_horizontal * \
		(texture->width / TILE_SIZE)), texture->width);
	else
		x_o = (int)fmodf((d->cast_rays.wall_hit_y_vertical * \
		(texture->width / TILE_SIZE)), texture->width);
	return (x_o);
}
void	draw_wall_texture(t_data *d, int t_pix, int b_pix, double wall_h)
{
	double			x_o;
	double			y_o;
	mlx_texture_t	*texture;
	unsigned int	*arr;
	double			factor;

	//check_side(d, nor_angle(d->data_player.angle_rotation));
	texture = get_texture_walls(d, d->cast_rays.flag);
	arr = (unsigned int *)texture->pixels;
	factor = (double)texture->height / wall_h;
	//x_o = get_x_o(texture, d);
	if (d->cast_rays.flag == 1)
		x_o = (int)fmodf((d->cast_rays.wall_hit_x_horizontal * (texture->width / TILE_SIZE)), texture->width);
	else
		x_o = (int)fmodf((d->cast_rays.wall_hit_y_vertical * (texture->width / TILE_SIZE)), texture->width);
	y_o = (t_pix - (HEIGHT / 2) + (wall_h / 2)) * factor;
	if (y_o < 0)
		y_o = 0;
	while (t_pix < b_pix)//aqui peta
	{
		safe_pixel_put(d->image, d->cast_rays.index, t_pix, reverse_bytes(arr[(int)y_o * texture->width + (int)x_o]));
		y_o += factor;
		t_pix++;
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