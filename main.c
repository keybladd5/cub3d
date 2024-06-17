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

void	ft_game_loop(void *param)
{
	t_data	*d;

	d = param;
	d->n_image = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	if (!d->n_image)
		ft_esc(d);
	ft_movement_hook(d);
	ft_render_scene(d);
	ft_draw_minimap(d, 0, 0);
	mlx_delete_image(d->mlx, d->image);
	d->image = d->n_image;
	if (mlx_image_to_window(d->mlx, d->image, 0, 0) == -1)
		ft_esc(d);
}

int	main(int argc, char **argv)
{
	t_data	d;

	if (ft_parse_input(argc, argv, &d.map))
		return (EXIT_FAILURE);
	init_data_map(&d);
	init_data_player(&d);
	d.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	if (!d.mlx)
		ft_esc(&d);
	d.n_image = mlx_new_image(d.mlx, WIDTH, HEIGHT);
	if (!d.n_image)
		ft_esc(&d);
	ft_render_scene(&d);
	ft_draw_minimap(&d, 0, 0);
	d.image = d.n_image;
	if (mlx_image_to_window(d.mlx, d.image, 0, 0) == -1)
		ft_esc(&d);
	mlx_loop_hook(d.mlx, ft_game_loop, &d);
	mlx_close_hook(d.mlx, ft_esc, (void *)(&d));
	mlx_loop(d.mlx);
	mlx_terminate(d.mlx);
	return (EXIT_SUCCESS);
}
