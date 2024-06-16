/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 23:44:54 by polmarti          #+#    #+#             */
/*   Updated: 2024/06/08 23:45:52 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Draws a square on the image buffer by painting pixels with the 
 * specified color.
 * 
 * @param image Pointer to the image buffer where the square is drawn.
 * @param map Pointer to the minimap structure defining the square's 
 * position and size.
 * @param color Color value to paint the square with.
 */

void	ft_draw_square(mlx_image_t *image, t_minimap *map, int color)
{
	int	y;
	int	x;

	x = map->x;
	y = map->y;
	while (y < map->y_limit)
	{
		x = map->x;
		while (x < map->x_limit)
		{
			if (x == map->x_limit - 1 || y == map->y_limit - 1 \
			|| x == map->x || y == map->y)
				safe_pixel_put(image, x, y, get_rgba(77, 77, 77, 255));
			else
				safe_pixel_put(image, x, y, color);
			x++;
		}
		y++;
	}
}

/**
 * Draws the player's position indicator on the minimap.
 * 
 * @param image Pointer to the image buffer where the minimap is drawn.
 * @param map Pointer to the minimap structure defining the rendering area.
 * @param color Color of the player indicator on the minimap.
 * @param ply Pointer to the player's data structure containing 
 * position information.
 */
static void	ft_draw_minimap_player(mlx_image_t *image, \
t_minimap *map, int color, t_data_player *ply)
{
	map->x = (ply->x / TILE_SIZE) * map->tile_size;
	map->x_limit = map->x + map->tile_size;
	map->y = (ply->y / TILE_SIZE) * map->tile_size;
	map->y_limit = map->y + map->tile_size;
	ft_draw_square(image, map, color);
}

/**
 * Draws the minimap based on the game map data onto 
 * the specified image buffer.
 * Each tile on the minimap represents a 
 * corresponding map cell in the game.
 *
 * @param d Pointer to the main data structure 
 * containing map information and image buffers.
 * @param y Starting y-coordinate of the minimap rendering.
 * @param x Starting x-coordinate of the minimap rendering.
 */
void	ft_draw_minimap(t_data *d, int y, int x)
{
	d->minimap.x = 0;
	d->minimap.x_limit = d->map.size_x * d->minimap.tile_size;
	d->minimap.y = 0;
	d->minimap.y_limit = d->map.size_y * d->minimap.tile_size;
	ft_draw_square(d->n_image, &(d->minimap), get_rgba(0, 0, 0, 255));
	d->minimap.y_limit = d->minimap.tile_size;
	while (y < d->map.size_y)
	{
		x = 0;
		d->minimap.x = 0;
		d->minimap.x_limit = d->minimap.tile_size;
		while (d->map.map[y][x])
		{
			if (d->map.map[y][x] == '1')
				ft_draw_square(d->n_image, &(d->minimap), 0xFFFFFFFF);
			x++;
			d->minimap.x += d->minimap.tile_size;
			d->minimap.x_limit += d->minimap.tile_size;
		}
		y++;
		d->minimap.y += d->minimap.tile_size;
		d->minimap.y_limit += d->minimap.tile_size;
	}
	ft_draw_minimap_player(d->n_image, &(d->minimap), \
	get_rgba(39, 245, 54, 255), &(d->data_player));
}
