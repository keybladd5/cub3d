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
	d.map[1] = ft_strdup("10000001");
	d.map[2] = ft_strdup("10P00001");
	d.map[3] = ft_strdup("10000001");
	d.map[4] = ft_strdup("10000001");
	d.map[5] = ft_strdup("11111111");
	d.map[6] = NULL;
	//he añadido una serie de datos relevantes al player, que necesito pasar por referencia
	//sin mallocs
	d.data_player.advance = 0;
	d.data_player.turn_on =  0;
	d.data_player.angle_rotation = M_PI;
	d.data_player.speed_advance = 3.0;
	d.data_player.speed_advance = 3.0;
	d.data_player.speed_turn_on = 1.0 * (M_PI / 180.0);
	d.data_player.x = 200;
	d.data_player.y = 200;
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
