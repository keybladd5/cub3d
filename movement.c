/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:14:49 by polmarti          #+#    #+#             */
/*   Updated: 2024/05/27 12:14:50 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_movement_hook(void *param)
{
	t_data *d = param;
	//implementacion de los hooks con datos como 1 o -1, para multiplicar por la velocidad de steps o speed_avance / speed_turn_on
	if (mlx_is_key_down(d->mlx, MLX_KEY_ESCAPE))
	{
		ft_free_map(d->map);
		return (mlx_close_window(d->mlx));
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_W) == true)
	{
		d->data_player.advance += 1;
		printf("advance\n");
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_S) == true)
		d->data_player.advance -= 1;
	if (mlx_is_key_down(d->mlx, MLX_KEY_D) == true)
		d->data_player.turn_on = 1;
	if (mlx_is_key_down(d->mlx, MLX_KEY_A) == true)
		d->data_player.turn_on = -1;
	d->data_player.angle_rotation += (d->data_player.turn_on * d->data_player.speed_turn_on);
	d->data_player.angle_rotation = nor_angle(d->data_player.angle_rotation);
	ft_move_player(d);
	ft_cast_rays(d);
	//hola ales, esto es setear los valores a 0 cuando ya se han pulsado, es mi implementacion del hook_key_release
	if (d->data_player.advance != 0)
		d->data_player.advance = 0;
	if (d->data_player.turn_on != 0)
		d->data_player.turn_on = 0;

}

void ft_move_player(t_data *d)
{
	int new_x;
	int new_y;
	new_x =  roundf(d->data_player.x  + (d->data_player.advance * cos(d->data_player.angle_rotation) * d->data_player.speed_advance)); 
	new_y =  roundf(d->data_player.y  +  (d->data_player.advance * sin(d->data_player.angle_rotation) * d->data_player.speed_advance));
	int map_grid_x = (new_x / TILE_SIZE); // get the x position in the map
	int map_grid_y = (new_y / TILE_SIZE); 
	//checkeo de colisiones
	printf("d->data_player.x -> %d d->data_player.y -> %d d->data_player.angle_rotation = %f\n", d->data_player.x, d->data_player.y, d->data_player.angle_rotation );
	printf("new_x -> %d new_y -> %d\n", new_x, new_y);
	if (d->map[map_grid_y][map_grid_x] != '1' && \
	(d->map[map_grid_y][d->data_player.x / TILE_SIZE] != '1' && \
	d->map[d->data_player.y / TILE_SIZE][map_grid_x] != '1')) // check the wall hit and the diagonal wall hit)
	{	
		printf("no hay impacto\n");
		d->data_player.x = new_x;
		d->data_player.y = new_y;
	}

}