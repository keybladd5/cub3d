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

//libera el mapa
void ft_free_map(char **map)
{
	int i;

	i = 0;
	while(map[i])
	{
		printf("%p\n", map[i]);
		free(map[i]);
		i++;
	}
	printf("%p\n", map);
	free(map);
}
void ft_read_map(t_data *d, char **map)
{
	int y;
	int x;

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
void ft_game_loop(void *param)
{
	t_data *d = param;
	mlx_delete_image(d->mlx, d->image);
	d->image = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	ft_cast_rays(d);
	ft_movement_hook(d);
	mlx_image_to_window(d->mlx, d->image, 0, 0);
}

int main(void)
{
	t_data	d;

	d.map = ft_calloc(8, sizeof(char *)); // init the map
	d.map[0] = ft_strdup("11111111"); //fill the map
	d.map[1] = ft_strdup("10010001");
	d.map[2] = ft_strdup("10010001");
	d.map[3] = ft_strdup("100P0001");
	d.map[4] = ft_strdup("10010001");
	d.map[5] = ft_strdup("11111111");
	d.map[6] = NULL;
	//he añadido una serie de datos relevantes al player, que necesito pasar por referencia
	//sin mallocs
	ft_read_map(&d, d.map);
	//d.map_x = 2;
	//d.map_y = 2;
	d.fish_eye = 0;
	d.data_player.advance = 0;
	d.data_player.turn_on =  0;
	d.data_player.angle_rotation = 0.0;
	d.data_player.speed_advance = 5.0;
	d.data_player.speed_turn_on = 3.0 * (M_PI / 180.0);
	d.data_player.x = d.map_x * TILE_SIZE + TILE_SIZE / 2;
	d.data_player.y = d.map_x * TILE_SIZE + TILE_SIZE / 2;
	d.data_player.fov_radians = (FOV * M_PI) / 180;

	
	//nuevas variables añadidas para los rayos
	d.data_player.west = false;
	d.data_player.south = false;
	d.cast_rays.x_intercept = 0;
	d.cast_rays.y_intercept = 0;

	//carga la ventana
	d.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);

	//inicializa la imagen que contendra los rayos y dibuja el primero en el centro del FOV
	d.image = mlx_new_image(d.mlx, WIDTH, HEIGHT);
	ft_cast_rays(&d);
	mlx_image_to_window(d.mlx, d.image, 0, 0);

	//hooks a eventos 
	mlx_loop_hook(d.mlx, ft_game_loop, &d);
	mlx_loop(d.mlx);
	mlx_terminate(d.mlx);

	return (EXIT_SUCCESS);
}
