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
void ft_mlx_error(void)
{
	ft_putendl_fd((char *)mlx_strerror(mlx_errno), 2);
	exit(EXIT_FAILURE);
}

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

//get the size_x and size_y
void ft_get_size_map(t_data *d, char **map)
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
//parte para añadir un asset que represente al player, pero lo carga con transparencia 
/*void ft_load_texture_beta(t_data *d)
{
	mlx_delete_image(d->mlx, d->test);
	d->test =  mlx_texture_to_image(d->mlx, d->tex);
	if (!d->test)
		error();
	mlx_image_to_window(d->mlx, d->test, (WIDTH / 2) - 150, (3 * HEIGHT) / 4);
	mlx_set_instance_depth(d->test->instances, 0xFF);
}*/
void ft_game_loop(void *param)
{
	t_data *d = param;
	mlx_delete_image(d->mlx, d->image);
	d->image = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	if (!d->image)
		ft_mlx_error();
	ft_cast_rays(d);
	ft_movement_hook(d);
	mlx_image_to_window(d->mlx, d->image, 0, 0);
	//parte para añadir un asset que represente al player, pero lo carga con transparencia 
	//ft_load_texture_beta(d);
}

int main(void)
{
	t_data	d;

	d.map = ft_calloc(8, sizeof(char *)); // init the map
	d.map[0] = ft_strdup("11111111111"); //fill the map
	d.map[1] = ft_strdup("10010000001");
	d.map[2] = ft_strdup("10010000001");
	d.map[3] = ft_strdup("100P0001001");
	d.map[4] = ft_strdup("10010000001");
	d.map[4] = ft_strdup("10010000001");
	d.map[5] = ft_strdup("11111111111");
	d.map[6] = NULL;
	ft_get_size_map(&d, d.map);
	d.data_player.advance = 0;
	d.data_player.turn_on =  0;
	d.data_player.angle_rotation = 0.0;
	d.data_player.speed_advance = 3.0;
	d.data_player.speed_turn_on = 3.5 * (M_PI / 180.0);
	d.data_player.x = d.map_x * TILE_SIZE + TILE_SIZE / 2;
	d.data_player.y = d.map_x * TILE_SIZE + TILE_SIZE / 2;
	d.data_player.fov_radians = (FOV * M_PI) / 180;
	//d.tex.ea = malloc(sizeof(mlx_texture_t));
	d.tex.ea = mlx_load_png("./assets/ea.png");
	if(!d.tex.ea)
		ft_mlx_error();
	//d.tex.no = malloc(sizeof(mlx_texture_t));
	d.tex.no = mlx_load_png("./assets/no.png");
	if(!d.tex.no)
		ft_mlx_error();
	//d.tex.so = malloc(sizeof(mlx_texture_t));
	d.tex.so = mlx_load_png("./assets/so.png");
	if(!d.tex.so)
		ft_mlx_error();
	//d.tex.we = malloc(sizeof(mlx_texture_t));
	d.tex.we = mlx_load_png("./assets/we.png");
	if(!d.tex.we)
		ft_mlx_error();

	
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
	//parte para añadir un asset que represente al player, pero lo carga con transparencia 
	/*d.tex = mlx_load_png("test.png");
	//si la ima
	if (!d.tex)
		error();
	d.test =  mlx_texture_to_image(d.mlx, d.tex);
	mlx_image_to_window(d.mlx, d.test,  (WIDTH / 2) - 150, (3 * HEIGHT) / 4);*/

	//hooks a eventos 
	mlx_loop_hook(d.mlx, ft_game_loop, &d);
	mlx_loop(d.mlx);
	mlx_terminate(d.mlx);

	return (EXIT_SUCCESS);
}
