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

double nor_angle(double angle) // normalize the angle
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

//Si hay error de calculo, o impacto retorna 0, sino hay impacto retorna 1
int collider_checker(t_data *d, double y, double x)
{
	int		x_m;
	int		y_m;

	if (x < 0.0 || y < 0.0)
		return (0);
	x_m = floor(x  / TILE_SIZE); // get the x position in the map
	y_m = floor(y  / TILE_SIZE); // get the y position in the map
	if (y_m  >= 6 || y_m <= 0) //cambiar por tamaño mapa
		return (0);
	if (d->map[y_m] && x_m <= (int)strlen(d->map[y_m]))
		if (d->map[y_m][x_m] == '1')
			return (0);
	return (1);
}

int	unit_circle(double angle, char c)	// check the unit circle
{
	if (c == 'x')
	{
		if (angle > 0 && angle < M_PI)
			return (1); //d->data_player.south = true;
		//else
			////d->data_player.south = false;
	}
	else if (c == 'y')
	{
		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
			return (1); //d->data_player.west = true;
		//else
			//d->data_player.west = false;
	}
	return (0);
}

int	inter_check(double angle, double *inter, double *step, int is_horizon)	// check the intersection
{
	if (is_horizon)
	{
		if (angle > 0 && angle < M_PI)
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	else
	{
		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2)) 
		{
			*inter += TILE_SIZE;
			return (-1);
		}
		*step *= -1;
	}
	return (1);
}

double	get_h_inter(t_data *d, double angl)	// get the horizontal intersection
{
	double	h_x;
	double	h_y;
	double	x_step;
	double	y_step;
	int		pixel;

	y_step = TILE_SIZE;
	x_step = TILE_SIZE / tan(angl);
	h_y = floor(d->data_player.y / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &h_y, &y_step, 1);
	h_x = d->data_player.x + (h_y - d->data_player.y) / tan(angl);
	if ((unit_circle(angl, 'y') && x_step > 0) || (!unit_circle(angl, 'y') && x_step < 0)) // check x_step value
		x_step *= -1;
	while (collider_checker(d, h_y - pixel, h_x)) // check the wall hit whit the pixel value
	{
		h_x += x_step;
		h_y += y_step;
	}
	return (sqrt(pow(h_x - d->data_player.x, 2) + pow(h_y - d->data_player.y, 2))); // get the distance
}

double	get_v_inter(t_data *d, double angl)	// get the vertical intersection
{
	double	v_x;
	double	v_y;
	double	x_step;
	double	y_step;
	int		pixel;

	x_step = TILE_SIZE; 
	y_step = TILE_SIZE * tan(angl);
	v_x = floor(d->data_player.x / TILE_SIZE) * TILE_SIZE;
	pixel = inter_check(angl, &v_x, &x_step, 0); // check the intersection and get the pixel value
	v_y = d->data_player.y + (v_x - d->data_player.x ) * tan(angl);
	if ((unit_circle(angl, 'x') && y_step < 0) || (!unit_circle(angl, 'x') && y_step > 0)) // check y_step value
		y_step *= -1;
	while (collider_checker(d, v_y, v_x - pixel)) // check the wall hit whit the pixel value
	{
		v_x += x_step;
		v_y += y_step;
	}
	return (sqrt(pow(v_x - d->data_player.x, 2) + pow(v_y - d->data_player.y, 2)));
}

void render_walls(t_data *d, int ray)
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

	d->cast_rays.distance *= cos(nor_angle(d->cast_rays.ray_ngl - d->data_player.angle_rotation));
	wall_h = (TILE_SIZE / d->cast_rays.distance) * ((WIDTH / 2) / tan(d->data_player.fov_radians / 2));
	b_pix = (HEIGHT / 2) + (wall_h / 2);
	t_pix = (HEIGHT / 2) - (wall_h / 2);
	if (b_pix > HEIGHT) // check the bottom pixel
		b_pix = HEIGHT;
	if (t_pix < 0) // check the top pixel
		t_pix = 0;
	draw_wall(d, ray, t_pix, b_pix); // draw the wall
	draw_floor_ceiling(d, ray, t_pix, b_pix); // draw the floor and the ceiling
}

void ft_cast_rays(t_data *d)
{
	double x_collision;
	double y_collision;
	int ray = 0;
	d->cast_rays.ray_ngl = d->data_player.angle_rotation - (d->data_player.fov_radians / 2);
	d->cast_rays.ray_ngl = nor_angle(d->cast_rays.ray_ngl);
	while (ray < WIDTH)
	{
		printf("ray #%d, ray_ngl: %f\n", ray, d->cast_rays.ray_ngl);
		d->cast_rays.flag = 0;
		x_collision = get_h_inter(d, nor_angle(d->cast_rays.ray_ngl));
		y_collision = get_v_inter(d, nor_angle(d->cast_rays.ray_ngl));
		if (y_collision <= x_collision) // check the distance
			d->cast_rays.distance = y_collision; // get the distance
		else
		{
			d->cast_rays.distance = x_collision; // get the distance
			d->cast_rays.flag = 1; // flag for the wall
		}
		render_walls(d, ray);
		ray++;
		d->cast_rays.ray_ngl += (d->data_player.fov_radians / WIDTH);
	}
}
