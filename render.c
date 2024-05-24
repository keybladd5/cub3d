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

//Si hay error de calculo, o impacto retorna 0, sino hay impacto retorna 1
int collider_checker(t_data *d, double y, double x)
{
	int		x_m;
	int		y_m;

	if (x < 0.0 ||y < 0.0)
		return (0);
	x_m = floor (x  / TILE_SIZE); // get the x position in the map
	y_m = floor (y  / TILE_SIZE); // get the y position in the map
	if ((y_m >= HEIGHT || x_m >= WIDTH))
		return (0);
	printf("y_m = %d x_m = %d\n", y_m, x_m);
	if (y_m  > 6 || x_m > 8 || y_m < 0 || x_m < 0)
		return (0);
	if (d->map[y_m] && x_m <= (int)ft_strlen(d->map[y_m]))
		if (d->map[y_m][x_m] == '1')
			return (0);
	return (1);
}

double ft_horizontal_collision(t_data *d)
{
	double adjacent_side;
	double x_step;
	double y_step;
	int pixel = 0;

	//CALCULO DE DISTANCIA DE STEPS Y PIXEL
	y_step = TILE_SIZE;
	x_step = y_step / tan(d->data_player.angle_rotation);
	if (!d->data_player.south)
		y_step *= -1;
	if ((d->data_player.west && x_step > 0) || (!d->data_player.west && x_step < 0))
		x_step *= -1;

	//CALCULO DEL CATETO ADYACENTE Y LOS X Y QUE VAN A INTERCEPTAR
	d->data_player.y_intercept = floor(((d->data_player.y) / TILE_SIZE) * TILE_SIZE);
	if (d->data_player.south)
	{
		d->data_player.y_intercept += TILE_SIZE;		
		pixel -= 1;
	}
	else
		pixel += 1;
	adjacent_side = (d->data_player.y_intercept - d->data_player.y) / tan(d->data_player.angle_rotation);
	d->data_player.x_intercept = (d->data_player.x) + adjacent_side;


	// EL BUCLE DE COLISION HORIZONTAL
	int next_x_horizontal = d->data_player.x_intercept;
	int next_y_horizontal = d->data_player.y_intercept;

	while(collider_checker(d, next_x_horizontal, next_y_horizontal - pixel))
	{
		next_x_horizontal += x_step;
		next_y_horizontal += y_step;
	}
	d->data_player.wall_hit_x_horizontal = next_x_horizontal;
	d->data_player.wall_hit_y_horizontal = next_y_horizontal;

	return (sqrt(pow(d->data_player.wall_hit_x_horizontal - d->data_player.x, 2) + pow(d->data_player.wall_hit_y_horizontal - d->data_player.y, 2)));
}

double ft_vertical_collision(t_data *d)
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
	y_step = TILE_SIZE * tan(d->data_player.angle_rotation);
	if ((!d->data_player.south && y_step > 0) || (d->data_player.south && y_step < 0))
		y_step *= -1;

	//CALCULO DEL CATETO OPUESTO Y X Y QUE VAN A INTERCEPTAR
	d->data_player.x_intercept = floor(((d->data_player.x) / TILE_SIZE) * TILE_SIZE);
	if (!d->data_player.west)
	{
		pixel -= 1;
		d->data_player.x_intercept += TILE_SIZE;
	}
	else
		pixel += 1;
	oposite_side = (d->data_player.x_intercept - d->data_player.x) * tan(d->data_player.angle_rotation);
	d->data_player.y_intercept = (d->data_player.y) + oposite_side;
	next_y_vertical = d->data_player.y_intercept;
	next_x_vertical = d->data_player.x_intercept;

	//bucle de checkeo de colision en vertical
	while(collider_checker(d, next_y_vertical, next_x_vertical - pixel))
	{
		next_x_vertical += x_step;
		next_y_vertical += y_step;
	}
	d->data_player.wall_hit_x_vertical = next_x_vertical;
	d->data_player.wall_hit_y_vertical = next_y_vertical;
	return (sqrt(pow(d->data_player.wall_hit_x_vertical - d->data_player.x, 2) + pow(d->data_player.wall_hit_y_vertical - d->data_player.y, 2)));
}