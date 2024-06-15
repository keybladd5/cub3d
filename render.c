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
 * Normalizes an angle to ensure that it is always in the range 0 to 2π 
 * radians.
 * If the angle is negative, 2π is added to bring it within the range.
 * If the angle is greater than 2π, 2π is subtracted to bring it within 
 * the range.
 *
 * @param angle The angle to be normalized, in radians.
 * @return The normalized angle, in the range [0, 2π) radians.
 */
double	nor_angle(double angle) // normalize the angle
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

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
int	collider_checker(t_data *d, double y, double x)
{
	int		x_m;
	int		y_m;

	if (x < 0.0 || y < 0.0)
		return (0);
	x_m = floor(x  / TILE_SIZE);
	y_m = floor(y  / TILE_SIZE);
	if (y_m  >= d->size_y || x_m >= d->size_x)
		return (0);
	if (x_m < 0 || y_m < 0)
		return (0);
	if (d->map[y_m] && x_m <= (int)ft_strlen(d->map[y_m]))
		if (d->map[y_m][x_m] == '1')
			return (0);
	return (1);
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
void	check_side(t_data *d, double angle)
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
void render_scene(t_data *d, int ray)
{
	double	wall_h;
	double	bottom_pix;
	double	top_pix;


	d->cast_rays.distance *= cos(nor_angle\
	(d->cast_rays.ray_ngl - d->data_player.angle_rotation));
	wall_h = (TILE_SIZE / d->cast_rays.distance) * \
	((WIDTH >> 1) / tan(d->data_player.fov_radians * 0.5));
	bottom_pix = (HEIGHT >> 1) + (wall_h  * 0.5);
	top_pix = (HEIGHT >> 1) - (wall_h * 0.5);
	if (bottom_pix > HEIGHT)
		bottom_pix = HEIGHT;
	if (top_pix < 0)
		top_pix = 0;
	d->cast_rays.index = ray;
	draw_wall_texture(d, top_pix, bottom_pix, wall_h);
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
void	ft_cast_rays(t_data *d)
{
	double	x_collision;
	double	y_collision;
	int		ray;

	ray = 0;
	d->cast_rays.ray_ngl = \
	d->data_player.angle_rotation - (d->data_player.fov_radians * 0.5);
	d->cast_rays.ray_ngl = nor_angle(d->cast_rays.ray_ngl);
	while (ray < WIDTH)
	{
		d->cast_rays.flag = 0;
		x_collision = get_h_inter(d, nor_angle(d->cast_rays.ray_ngl));
		y_collision = get_v_inter(d, nor_angle(d->cast_rays.ray_ngl));
		if (y_collision <= x_collision)
			d->cast_rays.distance = y_collision;
		else
		{
			d->cast_rays.distance = x_collision;
			d->cast_rays.flag = 1;
		}
		render_scene(d, ray);
		ray++;
		d->cast_rays.ray_ngl += (d->data_player.fov_radians / WIDTH);
	}
}
