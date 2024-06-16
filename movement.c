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
/**
 * Exits the program, freeing resources and closing the window.
 *
 * @param param Pointer to the main data structure containing scene 
 * and graphics information.
 */
void	ft_esc(void *param)
{
	t_data	*d;

	d = param;
	ft_free_map(&d->map);
	if (d->image)
		mlx_delete_image(d->mlx, d->image);
	if (d->n_image)
		mlx_delete_image(d->mlx, d->n_image);
	mlx_close_window(d->mlx);
	mlx_terminate(d->mlx);
	exit(1);
}

/**
 * Catch the press on keyboard and change 
 * player data based on the keys pressed.
 *
 * @param d Pointer to the main data structure 
 * containing scene, player, and input information.
 */
void	ft_hook(t_data *d)
{
	if (mlx_is_key_down(d->mlx, MLX_KEY_ESCAPE))
		ft_esc((void *)d);
	if (mlx_is_key_down(d->mlx, MLX_KEY_W) == true)
		d->data_player.advance += 1;
	if (mlx_is_key_down(d->mlx, MLX_KEY_S) == true)
		d->data_player.advance -= 1;
	if (mlx_is_key_down(d->mlx, MLX_KEY_RIGHT) == true)
		d->data_player.turn_on = 1;
	if (mlx_is_key_down(d->mlx, MLX_KEY_LEFT) == true)
		d->data_player.turn_on = -1;
	if (mlx_is_key_down(d->mlx, MLX_KEY_D) == true)
	{
		d->data_player.lateral_move = 1;
		d->data_player.advance = 1;
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_A) == true)
	{
		d->data_player.lateral_move = -1;
		d->data_player.advance = 1;
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_LEFT_SHIFT) == true)
		d->data_player.speed_advance = 8.0;
}

/**
 * Handle the key hook to improve player movement
 *  and normalize data.
 *
 * @param d Pointer to the main data structure
 *  containing scene, player, and input information.
 */
void	ft_movement_hook(t_data	*d)
{
	ft_hook(d);
	d->data_player.angle_rotation += (d->data_player.turn_on \
	* d->data_player.speed_turn_on);
	d->data_player.angle_rotation = nor_angle(d->data_player.angle_rotation);
	ft_move_player(d);
	if (d->data_player.advance != 0)
		d->data_player.advance = 0;
	if (d->data_player.turn_on != 0)
		d->data_player.turn_on = 0;
	if (d->data_player.lateral_move != 0)
		d->data_player.lateral_move = 0;
	if (d->data_player.speed_advance == 8.0)
		d->data_player.speed_advance = 4.0;
}

/**
 * Moves the player based on current movement 
 * commands and updates position.
 *
 * @param d Pointer to the main data structure
 *  containing scene, player, and input information.
 */
void	ft_move_player(t_data *d)
{
	int		new_x;
	int		new_y;
	double	tmp_angle_rotation;

	if (d->data_player.lateral_move != 0)
		tmp_angle_rotation = d->data_player.angle_rotation + \
		(LATERAL_RADIANS * d->data_player.lateral_move);
	else
		tmp_angle_rotation = d->data_player.angle_rotation;
	new_x = roundf(d->data_player.x + (d->data_player.advance * \
	cos(tmp_angle_rotation) * d->data_player.speed_advance));
	new_y = roundf(d->data_player.y + (d->data_player.advance * \
	sin(tmp_angle_rotation) * d->data_player.speed_advance));
	if (collider_checker(d, new_y, new_x) \
	&& (collider_checker(d, new_y, d->data_player.x) \
	&& collider_checker(d, d->data_player.y, new_x)))
	{
		d->data_player.x = new_x;
		d->data_player.y = new_y;
	}
}
