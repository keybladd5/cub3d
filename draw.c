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

/**
 * Constructs a 32-bit color value (RGBA) from 
 * the provided red, green, blue, and alpha components.
 * Alpha (a) controls the transparency level: 
 * 0 is fully transparent, 255 is fully opaque.
 *
 * @param r Red component (0-255).
 * @param g Green component (0-255).
 * @param b Blue component (0-255).
 * @param a Alpha component (0-255), controls transparency.
 * @return Constructed RGBA color value.
 */
int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
/**
 * Safely puts a pixel of the specified color onto 
 * the image buffer at the given coordinates (x, y).
 * Coordinates outside the bounds of the image buffer 
 * (0 to WIDTH-1 for x, 0 to HEIGHT-1 for y) are ignored.
 *
 * @param image Pointer to the image buffer (mlx_image_t structure).
 * @param x X-coordinate of the pixel.
 * @param y Y-coordinate of the pixel.
 * @param color Color value to be placed at the specified coordinates (RGBA format).
 */
void	safe_pixel_put(mlx_image_t *image, int x, int y, int color)
{
	if (x < 0 || x >= WIDTH)
		return ;
	if (y < 0 || y >= HEIGHT)
		return ;
	mlx_put_pixel(image, x, y, color);
}

/**
 * Selects and returns the appropriate texture for 
 * rendering walls based on the direction
 * indicated by the flag. If flag is 0, selects 
 * between east and west textures; if flag is 1,
 * selects between south and north textures.
 *
 * @param d Pointer to the main data structure containing
 *  scene and graphics information.
 * @param flag Flag indicating the direction of the wall 
 * texture to select (0 for east/west, 1 for south/north).
 * @return Pointer to the selected texture.
 */
mlx_texture_t	*get_texture_walls(t_data *d, int flag)
{
	if (flag == 0)
	{
		if (d->data_player.west == true)
			return (d->map.tex.we);
		else
			return (d->map.tex.ea);
	}
	else
	{
		if (d->data_player.south == true)
			return (d->map.tex.so);
		else
			return (d->map.tex.no);
	}
}
/**
 * Draws a textured wall on the screen between the 
 * specified top and bottom pixels.
 * Calculates the scaling factor for the texture based on the wall height.
 * Sets the texture origin coordinates based on the 
 * collision point and ray direction.
 * Draws the pixels obtained from the texture array, 
 * reversed to adapt to RGB format.
 *
 * @param d Pointer to the main data structure containing 
 * scene and graphics information.
 * @param top_pix Top pixel index where the wall starts on the screen.
 * @param bottom_pix Bottom pixel index where the wall ends on the screen.
 * @param wall_h Height of the wall on the screen.
 */
void	draw_wall_texture(t_data *d, int top_pix, int bottom_pix, double wall_h)
{
	double			x_o;
	double			y_o;
	mlx_texture_t	*texture;
	double			factor;

	texture = get_texture_walls(d, d->cast_rays.flag);
	d->map.tex.arr = (unsigned int *)texture->pixels;
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
			safe_pixel_put(d->n_image, d->cast_rays.index, top_pix, \
			reverse_bytes(d->map.tex.arr[(int)y_o * texture->width + (int)x_o]));
		y_o += factor;
		top_pix++;
	}
}

/**
 * Renders the floor and ceiling for a given ray on the screen.
 * The first loop renders the floor starting from the bottom pixel (`b_pix`) 
 * up to the screen height (`HEIGHT`).
 * The second loop renders the ceiling from the top of 
 * the screen down to the top pixel (`t_pix`).
 *
 * @param d Pointer to the main data structure containing scene 
 * and graphics information.
 * @param ray Index of the ray being processed.
 * @param t_pix Top pixel index for rendering the ceiling.
 * @param b_pix Bottom pixel index for rendering the floor.
 */
void	draw_floor_ceiling(t_data *d, int ray, int t_pix, int b_pix)
{
	int		i;

	i = b_pix;
	while (i < HEIGHT)
		safe_pixel_put(d->n_image, ray, i++, get_rgba(189, 181, 125, 255));
	i = 0;
	while (i < t_pix)
		safe_pixel_put(d->n_image, ray, i++, get_rgba(255, 255, 255, 255));
}
