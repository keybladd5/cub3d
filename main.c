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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "colors.h"
#include "MLX42/include/MLX42/MLX42.h"

#define WIDTH 600
#define HEIGHT 800

//funcion para obtener el color al llamar a put_pixel
//si se llama a esta funcion con a en 0, hace el color completamente trnasparente, si se hace con 255, sin transparencia
int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

void ft_draw_square(mlx_image_t *image, int y_limit, int x_limit, int color)
{
	int y = 0;
	int x = 0;
	while (y < y_limit)
	{
		x = 0;
		while (x < x_limit)
		{

			if (color == 1)
				mlx_put_pixel(image, x, y,  get_rgba(0, 0, 0, 250));
			else
				mlx_put_pixel(image, x, y,  get_rgba(255, 0, 255, 250));
			x++;
		}
		y++;
	}

}
int main(void)
{
	mlx_t* mlx;
	mlx_image_t  *square_b;
	mlx_image_t  *square_w;
	char map[6][8] = {
        {'1', '1', '1', '1', '1', '\0'},
        {'1', '0', '0', '0', '1', '\0'},
        {'1', '0', '0', '0', '1', '\0'},
        {'1', '0', '0', '0', '1', '\0'},
        {'1', '1', '1', '1', '1', '\0'},
		NULL
    };
	mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	square_b = mlx_new_image(mlx, WIDTH / 10, HEIGHT  / 10);
	ft_draw_square(square_b, 80, 60, 2);
	square_w = mlx_new_image(mlx, WIDTH / 10, HEIGHT  / 10 );
	ft_draw_square(square_w, 80, 60, 2);
	int y = 0;
	int x = 0;
	while (y < 6)
	{
		x = 0;
		while (x < 8)
		{
			if (map[y][x] == '1')
				mlx_image_to_window(mlx, square_b, (x * 10), (y * 10));
			else if (map[y][x] == '0')
				mlx_image_to_window(mlx, square_w, (x * 10), (y * 10));
			x++;
		}
		y++;
	}
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
