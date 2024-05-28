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

int main(void)
{
	//carga la ventana
	d.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);

	/*//new_image define una imagen con sus tamaños y el ptr a la ventana, despues se dibuja con draw_square
	d.square_b = mlx_new_image(d.mlx, 100, 100);
	ft_draw_square(d.square_b, 100, 100, 1);
	d.square_w = mlx_new_image(d.mlx, 100, 100);
	ft_draw_square(d.square_w, 100, 100, 2);
	//se dibuja el mapa solo una vez
	ft_draw_map(&d);*/

	/*//dibuja el jugador en las coordenadas iniciales (200,200)
	d.player = mlx_new_image(d.mlx, 25, 25);
	ft_draw_square(d.player, 25, 25, 3);
	mlx_image_to_window(d.mlx, d.player, 200, 200);*/

	//inicializa la imagen que contendra los rayos y dibuja el primero en el centro del FOV
	d.image = mlx_new_image(d.mlx, WIDTH, HEIGHT);
	ft_cast_rays(&d);
	mlx_image_to_window(d.mlx, d.image, 0, 0);
	
	//dibuja la imagen de la linea en direccion 0 radianes y coordenadas para que el centro coincida con el player (coordenadas iniciales - tamaño player)
	/*d.line = mlx_new_image(d.mlx, 75, 75);
	ft_draw_line(d.line, 38, 38, 75, 38, 1); //x0,y0 = centro de la imagen (x / 2 + 1, y / 2 + 1). x1 = borde derecho (75), y1 = y0 (linea horizontal)
	mlx_image_to_window(d.mlx, d.line, 175, 175);*/
	
	//hooks a eventos 
	mlx_loop_hook(d.mlx, ft_hook, &d);
	mlx_loop(d.mlx);
	mlx_terminate(d.mlx);

	return (EXIT_SUCCESS);
}
