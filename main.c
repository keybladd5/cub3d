/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:39:48 by polmarti          #+#    #+#             */
/*   Updated: 2024/05/07 11:39:51 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

//print mlx errors on std_error and set exit_status on 1;
void	ft_mlx_error(void)
{
	ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2);
	exit(EXIT_FAILURE);
}

void	ft_game_loop(void *param)
{
	t_data	*d;

	d = param;
	d->n_image = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	if (!d->n_image)
		ft_mlx_error();
	ft_movement_hook(d);
	ft_render_scene(d);
	ft_draw_minimap(d, 0, 0);
	mlx_delete_image(d->mlx, d->image);
	d->image = d->n_image;
	mlx_image_to_window(d->mlx, d->image, 0, 0);
}

void	init_data_player(t_data *d)
{
	d->data_player.advance = 0;
	d->data_player.turn_on = 0;
	d->data_player.angle_rotation = 0.0;
	d->data_player.speed_advance = 4.0;
	d->data_player.speed_turn_on = 3.5 * (M_PI / 180.0);
	d->data_player.x = d->map.spawn_x * TILE_SIZE + (TILE_SIZE >> 1);
	d->data_player.y = d->map.spawn_y * TILE_SIZE + (TILE_SIZE >> 1);
	d->data_player.fov_radians = (FOV * M_PI) / 180;
	d->data_player.lateral_move = 0;
	d->data_player.west = false;
	d->data_player.south = false;
	if ((WIDTH * 0.25 / d->map.size_x) < (HEIGHT * 0.25 / d->map.size_y))
		d->minimap.tile_size = WIDTH * 0.25 / d->map.size_x;
	else
		d->minimap.tile_size = HEIGHT * 0.25 / d->map.size_y;
}
int	main(int argc, char **argv)
{
	t_data	d;

	//parte a sustituir con la version del ales
	if (ft_parse_input(argc, argv, &d.map))
		return(EXIT_FAILURE);

	init_data_player(&d);
	
	//parte a sustituir con la version del ales 
	d.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	d.n_image = mlx_new_image(d.mlx, WIDTH, HEIGHT);
	ft_render_scene(&d);
	ft_draw_minimap(&d, 0, 0);
	d.image = d.n_image;
	mlx_image_to_window(d.mlx, d.image, 0, 0);
	mlx_loop_hook(d.mlx, ft_game_loop, &d);
	mlx_close_hook(d.mlx, ft_esc, (void *)(&d));
	mlx_loop(d.mlx);
	mlx_terminate(d.mlx);
	return (EXIT_SUCCESS);
}
