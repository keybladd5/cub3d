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

void ft_movement_hook(t_data *d)
{

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
	
	//hola ales, esto es setear los valores a 0 cuando ya se han pulsado, es mi implementacion del hook_key_release
	if (d->data_player.advance != 0)
		d->data_player.advance = 0;
	if (d->data_player.turn_on != 0)
		d->data_player.turn_on = 0;
}

void ft_move_player(t_data *d)
{
	double new_x;
	double new_y;
	new_x =  d->data_player.x  + (d->data_player.advance * cos(d->data_player.angle_rotation) * d->data_player.speed_advance); 
	new_y =  d->data_player.y  +  (d->data_player.advance * sin(d->data_player.angle_rotation) * d->data_player.speed_advance);
}