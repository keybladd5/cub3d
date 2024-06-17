/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:53:21 by polmarti          #+#    #+#             */
/*   Updated: 2024/05/22 17:53:22 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Checks if a specific position on the map is free of collisions.
 * If the coordinates (x, y) are out of bounds or if the map cell contains
 * a '1' (indicating a wall), it returns 0. Otherwise, it returns 1.
 *
 * @param d Pointer to the main data structure containing player and map
 *  information.
 * @param y The y-coordinate to check for collisions.
 * @param x The x-coordinate to check for collisions.
 * @return 0 if the position is out of bounds or collides with a wall,
 *  1 otherwise.
 */
int	ft_check_coll(t_data *d, double y, double x)
{
	int		x_m;
	int		y_m;

	if (x < 0.0 || y < 0.0)
		return (0);
	x_m = floor(x / TILE_SIZE);
	y_m = floor(y / TILE_SIZE);
	if (y_m >= d->map.size_y || x_m >= d->map.size_x)
		return (0);
	if (d->map.map[y_m] && x_m <= (int)ft_strlen(d->map.map[y_m]))
	{
		if (d->map.map[y_m][x_m] == '1')
			return (0);
		return (1);
	}
	return (0);
}

/**
 * Determines whether the angle points south and/or west and updates
 * the corresponding boolean values in d->data_player.south 
 * and d->data_player.west.
 *
 * @param d Pointer to the main data structure 
 * containing player information.
 * @param angle The angle to determine directionality, in radians.
 */
void	ft_check_side(t_data *d, double angle)
{
	if (angle > 0 && angle < M_PI)
		d->data_player.south = true;
	else
		d->data_player.south = false;
	if (angle > (M_PI * 0.5) && angle < (3 * M_PI) * 0.5)
		d->data_player.west = true;
	else
		d->data_player.west = false;
}

/**
 * Renders the walls on the screen correcting fisheye distortion.
 * Calculates the height of the wall and the start and end pixels
 * to draw on the screen, then calls the functions that draw the wall,
 * the floor, and the ceiling.
 *
 * @param d Pointer to the main data structure containing 
 * scene and player information.
 * @param ray Index of the current ray being rendered.
 */
void	ft_ray_caster(t_data *d, int ray)
{
	double	height_wall;
	double	bottom_pix;
	double	top_pix;

	d->cast_rays.distance *= cos(ft_nor_angle \
	(d->cast_rays.ray_ngl - d->data_player.angle_rotation));
	if (!d->cast_rays.distance)
		d->cast_rays.distance = 1;
	height_wall = (TILE_SIZE / d->cast_rays.distance) * \
	((WIDTH >> 1) / tan(d->data_player.fov_radians * 0.5)); // punto clave
	bottom_pix = (HEIGHT >> 1) + (height_wall * 0.5);
	top_pix = (HEIGHT >> 1) - (height_wall * 0.5);
	if (bottom_pix > HEIGHT)
		bottom_pix = HEIGHT;
	if (top_pix < 0)
		top_pix = 0;
	d->cast_rays.index = ray;
	draw_wall_texture(d, top_pix, bottom_pix, height_wall);
	draw_floor_ceiling(d, ray, top_pix, bottom_pix);
}

/**
 * Launches rays from the player's position at various angles
 * within the field of vision. Calculates the intersections
 * with nearest horizontals and verticals for each ray,
 * determines which one is closest, and renders the walls on the screen.
 *
 * @param d Pointer to the main data structure containing 
 * scene and player information.
 */
void	ft_render_scene(t_data *d)
{
	double	h_collision;
	double	v_collision;
	int		ray;

	ray = -1;
	d->cast_rays.ray_ngl = \
	d->data_player.angle_rotation - (d->data_player.fov_radians * 0.5);
	while (++ray < WIDTH)
	{
		d->cast_rays.ray_ngl = ft_nor_angle(d->cast_rays.ray_ngl);
		h_collision = ft_get_hinter(d, d->cast_rays.ray_ngl);
		v_collision = ft_get_vinter(d, d->cast_rays.ray_ngl);
		if (v_collision <= h_collision)
		{
			d->cast_rays.distance = v_collision;
			d->cast_rays.collission = VERTICAL;
		}
		else
		{
			d->cast_rays.distance = h_collision;
			d->cast_rays.collission = HORIZONTAL;
		}
		ft_ray_caster(d, ray);
		d->cast_rays.ray_ngl += (d->data_player.fov_radians / WIDTH); //punto clave a repasar
	}
}
