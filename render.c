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

/*int check_collision(int x, int y)
{
	char g_map[7][9] = {
    {'1', '1', '1', '1', '1', '1', '1', '1', '\0'},
    {'1', '0', '0', '0', '0', '0', '0', '1', '\0'},
    {'1', '0', '0', '1', '1', '1', '0', '1', '\0'},
    {'1', '0', '0', '1', '0', '0', '0', '1', '\0'},
	{'1', '0', '0', '0', '0', '0', '0', '1', '\0'},
    {'1', '1', '1', '1', '1', '1', '1', '1', '\0'},
    };

	if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
		return 0;
	
}*/



double ft_horizontal_collision(t_data *d)
{
	int adjacent_side;
	int x_step;
	int y_step;
	char g_map[7][9] = {
    {'1', '1', '1', '1', '1', '1', '1', '1', '\0'},
    {'1', '0', '0', '0', '0', '0', '0', '1', '\0'},
    {'1', '0', '0', '1', '1', '1', '0', '1', '\0'},
    {'1', '0', '0', '1', '0', '0', '0', '1', '\0'},
	{'1', '0', '0', '0', '0', '0', '0', '1', '\0'},
    {'1', '1', '1', '1', '1', '1', '1', '1', '\0'},
    };

	//CALCULO DEL CATETO ADYACENTE Y LOS X Y QUE VAN A INTERCEPTAR
	d->data_player.y_intercept = ((d->player->instances[0].y + 12) / TILE_SIZE) * TILE_SIZE;
	if (d->data_player.south)
		d->data_player.y_intercept += TILE_SIZE;		
	adjacent_side = (int)((double)(d->data_player.y_intercept - (d->player->instances[0].y + 12)) / tan(d->data_player.angle_rotation));
	d->data_player.x_intercept = (d->player->instances[0].x + 12) + adjacent_side;
	//printf("x_intercept = %d y_intercept = %d\n", d->data_player.x_intercept, d->data_player.y_intercept);

	//CALCULO DE DISTANCIA DE STEPS
	y_step = TILE_SIZE;
	x_step = (int)((double)y_step / tan(d->data_player.angle_rotation));
	if (!d->data_player.south)
		y_step *= -1;
	if ((d->data_player.west && x_step > 0) || (!d->data_player.west && x_step < 0))
		x_step *= -1;
	
	//ahora se calcula la distancia e cada paso, con las variables next_y y next_x
	//PREPARAR TODO PARA EL BUCLE DE COLISION HORIZONTAL
	int next_x_horizontal = d->data_player.x_intercept;
	int next_y_horizontal = d->data_player.y_intercept;
	bool coll_horizontal = false;
	if (!d->data_player.south)
		next_y_horizontal--;

	while(!coll_horizontal && (next_x_horizontal >= 0 && next_y_horizontal >= 0 && next_x_horizontal < WIDTH && next_y_horizontal < HEIGHT && next_x_horizontal >= TILE_SIZE))
	{
		//CALCULO PARA LA COLISION HORIZONTAL
		printf("HORIZONTAL next_x_horizontal: %d, next_y_horizontal: %d\n", next_x_horizontal, next_y_horizontal);
		if (g_map[next_y_horizontal / TILE_SIZE][next_x_horizontal / TILE_SIZE] == '1') //si hay impacto en los ejes x
		{
			coll_horizontal = true;
			printf("FINALL HORIZONTAL next_x_horizontal: %d, next_y_horizontal: %d\n", next_x_horizontal, next_y_horizontal);
			d->data_player.wall_hit_x_horizontal = next_x_horizontal;
			d->data_player.wall_hit_y_horizontal = next_y_horizontal;
		}
		else
		{
			next_x_horizontal += x_step;
			next_y_horizontal += y_step;
		}
	}
	if ((d->data_player.wall_hit_x_horizontal == 0 && d->data_player.wall_hit_y_horizontal == 0) || !coll_horizontal)
	{
		d->data_player.wall_hit_x_horizontal = INT_MAX;
		d->data_player.wall_hit_y_horizontal = INT_MAX;
	}
	return (sqrt(pow(d->data_player.wall_hit_x_horizontal - d->player->instances[0].x, 2) + pow(d->data_player.wall_hit_y_horizontal - d->player->instances[0].y, 2)));
}

double ft_vertical_collision(t_data *d)
{
	int oposite_side = 0;
	int x_step = 0;
	int y_step = 0;
	int next_x_vertical = 0;
	int next_y_vertical = 0;
	bool coll_vertical = false;
	char g_map[7][9] = {
    {'1', '1', '1', '1', '1', '1', '1', '1', '\0'},
    {'1', '0', '0', '0', '0', '0', '0', '1', '\0'},
    {'1', '0', '0', '1', '1', '1', '0', '1', '\0'},
    {'1', '0', '0', '1', '0', '0', '0', '1', '\0'},
	{'1', '0', '0', '0', '0', '0', '0', '1', '\0'},
    {'1', '1', '1', '1', '1', '1', '1', '1', '\0'},
    };

	//CALCULO DEL CATETO OPUESTO Y X Y QUE VAN A INTERCEPTAR
	d->data_player.x_intercept = ((d->player->instances[0].x + 12) / TILE_SIZE) * TILE_SIZE;
	if (d->data_player.west)
		d->data_player.x_intercept--;//next_x_vertical--;
	oposite_side = (int)((double)(d->data_player.x_intercept - (d->player->instances[0].x + 12)) * tan(d->data_player.angle_rotation));
	d->data_player.y_intercept = (d->player->instances[0].y + 12) + oposite_side;
	next_y_vertical = d->data_player.y_intercept;
	next_x_vertical = d->data_player.x_intercept;
	//CALCULO DE DISTANCIAS DE STEPS
	x_step = TILE_SIZE;
	if (d->data_player.west)
		x_step *= -1;
	y_step = TILE_SIZE * tan(d->data_player.angle_rotation);
	if ((!d->data_player.south && y_step > 0) || (d->data_player.south && y_step < 0))
		y_step *= -1;
	//bucle de checkeo de colision en vertical
	while(!coll_vertical && (next_x_vertical >= 0 && next_y_vertical >= 0 && next_x_vertical <= WIDTH && next_y_vertical <= HEIGHT && next_y_vertical >= TILE_SIZE))
	{
		printf("VERTICAL next_x_vertical: %d, next_y_vertical: %d\n", next_x_vertical, next_y_vertical);
		printf("VERTICAL x_step: %d, y_step: %d\n", x_step, y_step);
		if (g_map[next_y_vertical / TILE_SIZE][next_x_vertical / TILE_SIZE] == '1') //si hay impacto en los ejes y
		{
			coll_vertical = true;
			printf("FINALL VERTICAL next_x_vertical: %d, next_y_vertical: %d\n", next_x_vertical, next_y_vertical);
			d->data_player.wall_hit_x_vertical = next_x_vertical;
			d->data_player.wall_hit_y_vertical = next_y_vertical;
		}
		else
		{
			next_x_vertical += x_step;
			next_y_vertical += y_step;
		}
	}
	if ((d->data_player.wall_hit_x_vertical == 0 && d->data_player.wall_hit_y_vertical == 0) || !coll_vertical)
	{	
		printf("COLLISION %d\n", coll_vertical);
		printf("NO SE HA CALCULADO EL VERTICAL PORQUE VERTICAL next_x_vertical: %d, next_y_vertical: %d\n", next_x_vertical, next_y_vertical);
		printf(" .wall_hit_x_vertical: %d, .wall_hit_x_vertical: %d\n", d->data_player.wall_hit_x_vertical, d->data_player.wall_hit_y_vertical);
		d->data_player.wall_hit_x_vertical = INT_MAX;
		d->data_player.wall_hit_y_vertical = INT_MAX;
	}
	return (sqrt(pow(d->data_player.wall_hit_x_vertical - d->player->instances[0].x, 2) + pow(d->data_player.wall_hit_y_vertical - d->player->instances[0].y, 2)));
}