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
	int		x_map;
	int		y_map;

	if (x < 0.0 || y < 0.0)
		return (0);
	x_map = floor(x / TILE_SIZE);
	y_map = floor(y / TILE_SIZE);
	if (y_map >= d->map.size_y || x_map >= d->map.size_x)
		return (0);
	if (d->map.map[y_map] && x_map <= (int)ft_strlen(d->map.map[y_map]))
	{
		if (d->map.map[y_map][x_map] == '1')
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
 * @param plane_dist (internal variable) Distance from the player to the
 * projection plane, defined as the adjacent side of the
 * triangle with an angle of fov / 2 and an opposite side of
 * WIDTH / 2. Using the tangent formula (tan = opposite / adjacent)
 * we isolate the adjacent side to obtain the value. The variable
 * is constant as it only depends on the FOV and the WIDTH.
 * @param height_wall contains the projected height of the wall 
 * in pixels, which will be used to draw the wall slice on the screen.
 * 
 *Thales' Theorem: Two right triangles that have the same angle, 
  with legs (CA1, CO1) and (CA2, CO2), always maintain the same 
  ratio between their legs, so that CO1/CA1 = CO2/CA2.
  In our case:

    CA1 = plane_dist (distance from the player to 
	the projection plane, in pixels)
    CO1 = height_wall / 2 (half the height of the wall, in pixels)
    CA2 = d->cast_rays.distance (distance from the player to the wall, 
	in our unit of measure (1 tile = 64))
    CO2 = TILE_SIZE / 2 (half the height of the wall, 
	in our unit of measure (64 / 2))

  The formula would be: height_wall/2 / plane_dist = 
  TILE_SIZE/2 / d->cast_rays.distance

  Solving for height_wall (the value to calculate): 
  height_wall = 2 * plane_dist * (TILE_SIZE/2 / d->cast_rays.distance)
 * 
 */
void	ft_ray_caster(t_data *d, int ray)
{
	double	height_wall;
	double	bottom_pix;
	double	top_pix;
	int		plane_dist;

	d->cast_rays.distance *= cos(ft_nor_angle \
	(d->cast_rays.ray_ngl - d->data_player.angle_rotation));
	if (!d->cast_rays.distance)
		d->cast_rays.distance = 1;
	plane_dist = ((WIDTH >> 1) / tan(d->data_player.fov_radians * 0.5));
	height_wall = 2 * plane_dist * ((TILE_SIZE >> 1) / d->cast_rays.distance);
	bottom_pix = (HEIGHT >> 1) + (height_wall * 0.5);
	top_pix = (HEIGHT >> 1) - (height_wall * 0.5);
	if (bottom_pix > HEIGHT)
		bottom_pix = HEIGHT;
	if (top_pix < 0)
		top_pix = 0;
	d->cast_rays.index = ray;
	ft_draw_texture(d, top_pix, bottom_pix, height_wall);
	ft_draw_fl_ce(d, ray, top_pix, bottom_pix);
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
	double	h_dist;
	double	v_dist;
	int		ray;

	ray = -1;
	d->cast_rays.ray_ngl = \
	d->data_player.angle_rotation - (d->data_player.fov_radians * 0.5);
	while (++ray < WIDTH)
	{
		d->cast_rays.ray_ngl = ft_nor_angle(d->cast_rays.ray_ngl);
		h_dist = ft_get_hinter(d, d->cast_rays.ray_ngl);
		v_dist = ft_get_vinter(d, d->cast_rays.ray_ngl);
		if (v_dist <= h_dist)
		{
			d->cast_rays.distance = v_dist;
			d->cast_rays.collission = VERTICAL;
		}
		else
		{
			d->cast_rays.distance = h_dist;
			d->cast_rays.collission = HORIZONTAL;
		}
		ft_ray_caster(d, ray);
		d->cast_rays.ray_ngl += (d->data_player.fov_radians / WIDTH);
	}
}
