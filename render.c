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
	if ((y_m >= HEIGHT || x_m >= WIDTH))
		return (0);
	printf("y_m = %d x_m = %d\n", y_m, x_m);
	if (y_m  > 6 || y_m < 0)
		return (0);
	if (d->map[y_m] && x_m <= (int)ft_strlen(d->map[y_m]))
		if (d->map[y_m][x_m] == '1')
			return (0);
	return (1);
}

double ft_horizontal_collision(t_data *d, double angle)
{
	double adjacent_side;
	double x_step;
	double y_step;
	int pixel = 0;

	//CALCULO DE DISTANCIA DE STEPS Y PIXEL
	y_step = TILE_SIZE;
	x_step = y_step / tan(angle);
	if (!d->data_player.south)
		y_step *= -1;
	if ((d->data_player.west && x_step > 0) || (!d->data_player.west && x_step < 0))
		x_step *= -1;

	//CALCULO DEL CATETO ADYACENTE Y LOS X Y QUE VAN A INTERCEPTAR
	d->cast_rays.y_intercept = floor(((d->data_player.y) / TILE_SIZE) * TILE_SIZE);
	if (d->data_player.south)
	{
		d->cast_rays.y_intercept += TILE_SIZE;		
		pixel -= 1;
	}
	else
		pixel += 1;
	adjacent_side = (d->cast_rays.y_intercept - d->data_player.y) / tan(angle);
	d->cast_rays.x_intercept = (d->data_player.x) + adjacent_side;


	// EL BUCLE DE COLISION HORIZONTAL
	int next_x_horizontal = d->cast_rays.x_intercept;
	int next_y_horizontal = d->cast_rays.y_intercept;

	while(collider_checker(d, next_x_horizontal, next_y_horizontal - pixel))
	{
		next_x_horizontal += x_step;
		next_y_horizontal += y_step;
	}
	d->cast_rays.wall_hit_x_horizontal = next_x_horizontal;
	d->cast_rays.wall_hit_y_horizontal = next_y_horizontal;

	return (sqrt(pow(d->cast_rays.wall_hit_x_horizontal - d->data_player.x, 2) + pow(d->cast_rays.wall_hit_y_horizontal - d->data_player.y, 2)));
}

double ft_vertical_collision(t_data *d, double angle)
{
	double oposite_side = 0;
	double x_step = 0;
	double y_step = 0;
	double next_x_vertical = 0;
	double next_y_vertical = 0;
	int pixel = 0;

	//CALCULO DE DISTANCIAS DE STEPS
	x_step = TILE_SIZE;
	if (d->data_player.west)
		x_step *= -1;
	y_step = TILE_SIZE * tan(angle);
	if ((!d->data_player.south && y_step > 0) || (d->data_player.south && y_step < 0))
		y_step *= -1;

	//CALCULO DEL CATETO OPUESTO Y X Y QUE VAN A INTERCEPTAR
	d->cast_rays.x_intercept = floor(((d->data_player.x) / TILE_SIZE) * TILE_SIZE);
	if (!d->data_player.west)
	{
		pixel -= 1;
		d->cast_rays.x_intercept += TILE_SIZE;
	}
	else
		pixel += 1;
	oposite_side = (d->cast_rays.x_intercept - d->data_player.x) * tan(angle);
	d->cast_rays.y_intercept = (d->data_player.y) + oposite_side;
	next_y_vertical = d->cast_rays.y_intercept;
	next_x_vertical = d->cast_rays.x_intercept;

	//bucle de checkeo de colision en vertical
	while(collider_checker(d, next_y_vertical, next_x_vertical - pixel))
	{
		next_x_vertical += x_step;
		next_y_vertical += y_step;
	}
	d->cast_rays.wall_hit_x_vertical = next_x_vertical;
	d->cast_rays.wall_hit_y_vertical = next_y_vertical;
	return (sqrt(pow(d->cast_rays.wall_hit_x_vertical - d->data_player.x, 2) + pow(d->cast_rays.wall_hit_y_vertical - d->data_player.y, 2)));
}

void render_walls(t_data *d, int ray)
{
	double	wall_h;
	double	b_pix;
	double	t_pix;

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
	while (ray < WIDTH)
	{
		d->cast_rays.flag = 0;
		x_collision = ft_horizontal_collision(d, nor_angle(d->data_player.angle_rotation));
		y_collision = ft_vertical_collision(d, nor_angle(d->data_player.angle_rotation));
		if (y_collision <= x_collision) // check the distance
			d->cast_rays.distance = y_collision; // get the distance
		else
		{
			d->cast_rays.distance =x_collision; // get the distance
			d->cast_rays.flag = 1; // flag for the wall
		}
		render_walls(d, ray);
		ray++;
		d->cast_rays.ray_ngl += (d->data_player.fov_radians / WIDTH);
	}
}
