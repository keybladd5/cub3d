/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_dda.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:42:48 by polmarti          #+#    #+#             */
/*   Updated: 2024/06/15 17:42:53 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Initializes DDA (Digital Differential Analyzer) data for 
 * horizontal intersections.
 * Sets the initial step sizes and intersection coordinates based 
 * on the angle of the ray.
 * Determines the direction of the ray (south or north) and adjusts 
 * steps accordingly.
 *
 * @param d Pointer to the main data structure containing player and map 
 * information.
 * @param angl The angle of the ray being cast.
 * @param h Pointer to a structure that will store the DDA data for 
 * horizontal intersections.
 */
static void	aux_get_h_inter(t_data *d, double angl, t_dda_data *h)
{
	h->y_step = TILE_SIZE;
	h->x_step = TILE_SIZE / tan(angl);
	h->dda_y = floor(d->data_player.y / TILE_SIZE) * TILE_SIZE;
	check_side(d, nor_angle(angl));
	if (d->data_player.south == true)
	{
		h->dda_y += TILE_SIZE;
		h->pixel = -1;
	}
	else
	{
		h->pixel = 1;
		h->y_step *= -1;
	}
	h->dda_x = d->data_player.x + (h->dda_y - d->data_player.y) / tan(angl);
	if ((d->data_player.west == true && h->x_step > 0) \
	|| (d->data_player.west == false && h->x_step < 0))
		h->x_step *= -1;
}

/**
 * Calculates the closest horizontal intersection of a ray launched 
 * from the player's position at a given angle.
 * Uses DDA to step through the grid and find 
 * the nearest horizontal wall intersection.
 * Updates the intersection coordinates in the main data structure.
 *
 * @param d Pointer to the main data structure containing 
 * player and map information.
 * @param angl The angle of the ray being cast.
 * @return The distance from the player to the nearest 
 * horizontal intersection.
 */
double	get_h_inter(t_data *d, double angl)
{
	t_dda_data  h;

	aux_get_h_inter(d, angl, &h);
	while (collider_checker(d, h.dda_y - h.pixel, h.dda_x))
	{
		h.dda_x += h.x_step;
		h.dda_y += h.y_step;
	}
	d->cast_rays.wall_hit_x_horizontal = h.dda_x;
	d->cast_rays.wall_hit_y_horizontal = h.dda_y;
	return (sqrt(pow(h.dda_x - d->data_player.x, 2) \
    + pow(h.dda_y - d->data_player.y, 2)));
}
/**
 * Initializes DDA (Digital Differential Analyzer) 
 * data for vertical intersections.
 * Sets the initial step sizes and intersection 
 * coordinates based on the angle of the ray.
 * Determines the direction of the ray (west or east) 
 * and adjusts steps accordingly.
 *
 * @param d Pointer to the main data structure 
 * containing player and map information.
 * @param angl The angle of the ray being cast.
 * @param v Pointer to a structure that will 
 * store the DDA data for vertical intersections.
 */
static void    aux_get_v_inter(t_data *d, double angl, t_dda_data *v)
{
    v->x_step = TILE_SIZE;
	v->y_step = TILE_SIZE * tan(angl);
	v->dda_x = floor(d->data_player.x / TILE_SIZE) * TILE_SIZE;
	check_side(d, nor_angle(angl));
	if (d->data_player.west == false)
	{
		v->dda_x += TILE_SIZE;
		v->pixel = -1;
	}
	else
	{
		v->pixel = 1;
		v->x_step *= -1;
	}
	v->dda_y = d->data_player.y + (v->dda_x - d->data_player.x) * tan(angl);
	if ((d->data_player.south == true && v->y_step < 0) \
    || (d->data_player.south == false && v->y_step > 0))
		v->y_step *= -1;
}

/**
 * Calculates the closest vertical intersection of a ray 
 * launched from the player's position at a given angle.
 * Uses DDA to step through the grid and find the 
 * nearest vertical wall intersection.
 * Updates the intersection coordinates in the main 
 * data structure.
 *
 * @param d Pointer to the main data structure 
 * containing player and map information.
 * @param angl The angle of the ray being cast.
 * @return The distance from the player to the 
 * nearest vertical intersection.
 */
double	get_v_inter(t_data *d, double angl)
{
    t_dda_data  v;
    aux_get_v_inter(d, angl, &v);
	while (collider_checker(d, v.dda_y, v.dda_x - v.pixel))
	{
		v.dda_x += v.x_step;
		v.dda_y += v.y_step;
	}
	d->cast_rays.wall_hit_x_vertical = v.dda_x;
	d->cast_rays.wall_hit_y_vertical = v.dda_y;
	return (sqrt(pow(v.dda_x - d->data_player.x, 2) + \
    pow(v.dda_y - d->data_player.y, 2)));
}

