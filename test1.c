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

//funcion para obtener el color al llamar a put_pixel
//si se llama a esta funcion con a en 0, hace el color completamente trnasparente, si se hace con 255, sin transparencia
int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_hook(void* param)
{
	t_data *d = param;

	//SOLO UTIL PARA TESTEAR COLISIONES
	char map[7][9] = {
    {'1', '1', '1', '1', '1', '1', '1', '1', '\0'},
    {'1', '0', '0', '0', '0', '0', '0', '1', '\0'},
    {'1', '0', '0', '0', '0', '0', '0', '1', '\0'},
    {'1', '0', '0', '0', '0', '0', '0', '1', '\0'},
	{'1', '0', '0', '0', '0', '0', '0', '1', '\0'},
    {'1', '1', '1', '1', '1', '1', '1', '1', '\0'},
    };

	if (mlx_is_key_down(d->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(d->mlx);
	//en las siguientes condiciones, se modifica la instancia de la imagen ya cargada en pantalla, info obtenida de 
	//https://github.com/codam-coding-college/MLX42/blob/master/docs/Images.md
	
	//el hook revisa si la posicion a donde va a avanzar es un '0', si es asi modifica la posicion de la imagen.
	if (mlx_is_key_down(d->mlx, MLX_KEY_W))
	{
		if (map[(d->player->instances[0].y - 5) / 100][d->player->instances[0].x / 100] == '0')
			d->player->instances[0].y -= 5;
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_S))
	{
		if (map[(d->player->instances[0].y + 5) / 100][d->player->instances[0].x / 100] == '0')
			d->player->instances[0].y += 5;
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_A))
	{
		if (map[d->player->instances[0].y / 100][(d->player->instances[0].x - 5) / 100] == '0')
			d->player->instances[0].x -= 5;
	}
	if (mlx_is_key_down(d->mlx, MLX_KEY_D))
	{
		if (map[d->player->instances[0].y / 100][(d->player->instances[0].x + 5) / 100] == '0')
			d->player->instances[0].x += 5;
	}
}

void ft_draw_square(mlx_image_t *image, int x_limit, int y_limit, int color)
{
	int y = 0;
	int x = 0;
	while (y < y_limit)
	{
		x = 0;
		while (x < x_limit)
		{
			//condicion para dibujar los limites en verde del square
			if (x == x_limit - 1 || y == y_limit - 1 || x == 0 || y == 0)
				mlx_put_pixel(image, x, y,  get_rgba(0, 0, 0, 255));
			//si la llamada es para tipo CONTENIDO DEL MAPA
			else if (color == 2)
				mlx_put_pixel(image, x, y,  get_rgba(71, 66, 71, 250));
			//sino si la llamada es para tipo LIMITE DEL MAPA
			else if (color == 1)
				mlx_put_pixel(image, x, y,  get_rgba(46, 14, 46, 255));
			else if (color == 3)
				mlx_put_pixel(image, x, y,  get_rgba(235, 52, 64, 255));
			x++;
		}
		y++;
	}
}

void ft_draw_player(mlx_t* mlx, mlx_image_t *player, int x, int y)
{
	ft_draw_square(player, 20, 20, 3);
	mlx_image_to_window(mlx, player, x, y);
}

void ft_draw_map(void *data)
{
	t_data *d = data;
	//mapa de ejemplo adaptado a las macros + 1 (para el null) de WIDTH (800) y HEIGHT (600)
	char map[7][9] = {
        {'1', '1', '1', '1', '1', '1', '1', '1', '\0'},
        {'1', '0', '0', '0', '0', '0', '0', '1', '\0'},
        {'1', '0', '0', '0', '0', '0', '0', '1', '\0'},
        {'1', '0', '0', '0', '0', '0', '0', '1', '\0'},
		{'1', '0', '0', '0', '0', '0', '0', '1', '\0'},
        {'1', '1', '1', '1', '1', '1', '1', '1', '\0'},
    };

	int y = 0;
	int x = 0;
	//buncle que renderiza la imagen de la ventana una vez 
	while (y < 6)
	{
		x = 0;
		while (x < 8)
		{
			if (map[y][x] == '1')
			{
				//printf("| %p  x = %d y = %d  |", square_b, (x * 100), (y *  100));
				mlx_image_to_window(d->mlx, d->square_b, (x * 100), (y * 100));
			}
			else if (map[y][x] == '0')
			{
				//printf("| %p  x = %d y = %d  |", square_w, (x * 100), (y *  100));
				mlx_image_to_window(d->mlx, d->square_w, (x * 100), (y *  100));
			}
			x++;
		}
		//printf("\n");
		y++;
	}
	ft_draw_player(d->mlx, d->player, 200, 200);
}
int main(void)
{
	t_data	*d;
	//carga la ventana
	d->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);

	//new_image define una imagen con sus tamaños y el ptr a la ventana, despues se dibuja con draw_square
	d->square_b = mlx_new_image(d->mlx, 100, 100);
	ft_draw_square(d->square_b, 100, 100, 1);

	//new_image define una imagen con sus tamaños y el ptr a la ventana, despues se dibuja con draw_square
	d->square_w = mlx_new_image(d->mlx, 100, 100);
	ft_draw_square(d->square_w, 100, 100, 2);

	d->player = mlx_new_image(d->mlx, 30, 20);

	ft_draw_map(d);
	mlx_loop_hook(d->mlx, ft_hook, d);
	//mlx_loop_hook(d->mlx, ft_draw_map, d);	
	mlx_loop(d->mlx);
	mlx_terminate(d->mlx);
	return (EXIT_SUCCESS);
}
