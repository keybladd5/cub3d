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

void ft_draw_square(mlx_image_t *image, t_minimap *map,  int color)
{
	int y;
	int x;

    x = map->x;
    y = map->y;
	while (y < map->y_limit)
	{
		x = map->x;
		while (x < map->x_limit)
		{
			if (x == map->x_limit - 1 || y == map->y_limit - 1 || x == map->x || y == map->y)
				safe_pixel_put(image, x, y,  get_rgba(77, 77, 77, 255));
			else
                safe_pixel_put(image, x, y,  color);
			x++;
		}
		y++;
	}
}

void ft_draw_minimap(t_data *d)
{
    int y = 0;
    int x = 0;
    d->minmap.x = 0;
    d->minmap.x_limit = d->size_x * MINIMAP_TILE_SIZE;
    d->minmap.y = 0;
    d->minmap.y_limit = d->size_y * MINIMAP_TILE_SIZE;
    ft_draw_square(d->image, &(d->minmap), get_rgba(0,0,0,255));
    d->minmap.y_limit = MINIMAP_TILE_SIZE;
    while (y < d->size_y)
    {
        x = 0;
        d->minmap.x = 0;
        d->minmap.x_limit = MINIMAP_TILE_SIZE;
        while (x < d->size_x)
        {
            if (d->map[y][x] == '1')
               ft_draw_square(d->image, &(d->minmap), get_rgba(255,255,255,255));
            x++;
            d->minmap.x += MINIMAP_TILE_SIZE;
            d->minmap.x_limit += MINIMAP_TILE_SIZE;
        }
        y++;
        d->minmap.y += MINIMAP_TILE_SIZE;
        d->minmap.y_limit += MINIMAP_TILE_SIZE;
    }
    d->minmap.x = (d->data_player.x / TILE_SIZE) * MINIMAP_TILE_SIZE;
    d->minmap.x_limit = d->minmap.x + MINIMAP_TILE_SIZE;
    d->minmap.y = (d->data_player.y / TILE_SIZE) * MINIMAP_TILE_SIZE;
    d->minmap.y_limit = d->minmap.y + MINIMAP_TILE_SIZE;
    ft_draw_square(d->image, &(d->minmap), get_rgba(39,245,54,255));
}
