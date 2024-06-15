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

//libera el mapa
void	ft_free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%p\n", map[i]);
		free(map[i]);
		i++;
	}
	printf("%p\n", map);
	free(map);
}

//get the size_x and size_y
void	ft_get_size_map(t_data *d, char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			x++;
			if (map[y][x] == 'P')
			{
				d->map_x = x;
				d->map_y = y;
			}
			if (!map[y][x])
				d->size_x = x;
		}
		y++;
	}
	d->size_y = y;
}

void	ft_game_loop(void *param)
{
	t_data	*d;

	d = param;
	mlx_delete_image(d->mlx, d->image);
	d->image = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	if (!d->image)
		ft_mlx_error();
	ft_movement_hook(d);
	ft_cast_rays(d);
	ft_draw_minimap(d, 0, 0);
	mlx_image_to_window(d->mlx, d->image, 0, 0);
}
int	main(void)
{
	t_data	d;

	d.map = ft_calloc(10, sizeof(char *));
	d.map[0] = ft_strdup("11111111111");
	d.map[1] = ft_strdup("10000001001");
	d.map[2] = ft_strdup("101110010101");
	d.map[3] = ft_strdup("101 1P100001");
	d.map[4] = ft_strdup("101 10011001");
	d.map[5] = ft_strdup("101 101  101");
	d.map[6] = ft_strdup("101 10111101");
	d.map[7] = ft_strdup("101 10000001");
	d.map[8] = ft_strdup("11  11111111");
	d.map[9] = NULL;
	ft_get_size_map(&d, d.map);
	d.data_player.advance = 0;
	d.data_player.turn_on = 0;
	d.data_player.angle_rotation = 0.0;
	d.data_player.speed_advance = 4.0;
	d.data_player.speed_turn_on = 3.5 * (M_PI / 180.0);
	d.data_player.x = d.map_x * TILE_SIZE + (TILE_SIZE >> 1);
	d.data_player.y = d.map_x * TILE_SIZE + (TILE_SIZE >> 1);
	d.data_player.fov_radians = (FOV * M_PI) / 180;
	d.data_player.lateral_move = 0;
	d.data_player.west = false;
	d.data_player.south = false;
	d.tex.ea = mlx_load_png("./assets/ea.png");
	if (!d.tex.ea)
		ft_mlx_error();
	d.tex.no = mlx_load_png("./assets/no.png");
	if (!d.tex.no)
		ft_mlx_error();
	d.tex.so = mlx_load_png("./assets/so.png");
	if (!d.tex.so)
		ft_mlx_error();
	d.tex.we = mlx_load_png("./assets/we.png");
	if (!d.tex.we)
		ft_mlx_error();
	d.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);
	d.image = mlx_new_image(d.mlx, WIDTH, HEIGHT);
	ft_cast_rays(&d);
	ft_draw_minimap(&d, 0, 0);
	mlx_image_to_window(d.mlx, d.image, 0, 0);
	mlx_loop_hook(d.mlx, ft_game_loop, &d);
	mlx_close_hook(d.mlx, ft_esc, (void *)(&d));
	mlx_loop(d.mlx);
	mlx_terminate(d.mlx);
	return (EXIT_SUCCESS);
}
