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
		d->data_player.advance += 1;
	if (mlx_is_key_down(d->mlx, MLX_KEY_S) == true)
		d->data_player.advance -= 1;
	if (mlx_is_key_down(d->mlx, MLX_KEY_D) == true)
		d->data_player.turn_on = 1;
	if (mlx_is_key_down(d->mlx, MLX_KEY_A) == true)
		d->data_player.turn_on = -1;
	if (mlx_is_key_down(d->mlx, MLX_KEY_RIGHT) == true)
	{
		d->data_player.lateral_move = 1;
		d->data_player.advance += 1;
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_RIGHT) == true)
	{
		d->data_player.lateral_move = -1;
		d->data_player.advance += 1;
	}
		//funcion que que setea una flag que indica(resta 90 grados) y pone advance en +1
	//if (mlx_is_key_down(d->mlx, MLX_KEY_LEFT) == true)
		//funcion que que setea una flag que indica(suma 90 grados) y pone advance en +1
	d->data_player.angle_rotation += (d->data_player.turn_on * d->data_player.speed_turn_on);
	d->data_player.angle_rotation = nor_angle(d->data_player.angle_rotation);
 	//parte para añadir el desplazamiento lateral pero no funciona bien, ademas pendiente incorporar el collider antes de desplazar
	/*if (mlx_is_key_down(d->mlx, MLX_KEY_RIGHT))
	{
		d->data_player.x  = d->data_player.x - cos(LATERAL_RADIANS - nor_angle(d->data_player.angle_rotation)) * 1;
		d->data_player.y  = d->data_player.y + sin(LATERAL_RADIANS - nor_angle(d->data_player.angle_rotation)) * 1;
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_LEFT))
	{
		d->data_player.x  = d->data_player.x + cos(LATERAL_RADIANS - nor_angle(d->data_player.angle_rotation)) * 1;
		d->data_player.y  = d->data_player.y - sin(LATERAL_RADIANS - nor_angle(d->data_player.angle_rotation)) * 1;
	}*/
	ft_move_player(d);
	ft_cast_rays(d);
	if (d->data_player.advance != 0)
		d->data_player.advance = 0;
	if (d->data_player.turn_on != 0)
		d->data_player.turn_on = 0;
	if (d->data_player.lateral_move != 0)
		d->data_player.lateral_move = 0;

}

void ft_move_player(t_data *d)
{
	int new_x;
	int new_y;

	if (d->data_player.lateral_move != 0)
		d->data_player.angle_rotation += LATERAL_RADIANS * d->data_player.lateral_move;
	new_x =  roundf(d->data_player.x  + (d->data_player.advance * cos(d->data_player.angle_rotation) * d->data_player.speed_advance)); 
	new_y =  roundf(d->data_player.y  +  (d->data_player.advance * sin(d->data_player.angle_rotation) * d->data_player.speed_advance));
	//checkeo de colisiones
	if (collider_checker(d, new_y , new_x)&& (collider_checker(d, new_y , d->data_player.x) && collider_checker(d, d->data_player.y, new_x))) // check the wall hit and the diagonal wall hit)
	{	
		d->data_player.x = new_x;
		d->data_player.y = new_y;
	}

}