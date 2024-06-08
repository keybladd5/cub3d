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

int main(int argc, char **argv)
{
	t_data	d;

	if (ft_parse_input(argc, argv, &d.map))
		return(EXIT_FAILURE);

	//free all allocated memory
	ft_free_map(&d.map);
	return (EXIT_SUCCESS);
}

/*
	d = ft_calloc(1, sizeof(t_data));




	//carga la ventana
	d.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);

	//inicializa la imagen que contendra los rayos y dibuja el primero en el centro del FOV
	d.image = mlx_new_image(d.mlx, WIDTH, HEIGHT);
	ft_cast_rays(&d);
	mlx_image_to_window(d.mlx, d.image, 0, 0);
	
	//dibuja la imagen de la linea en direccion 0 radianes y coordenadas para que el centro coincida con el player (coordenadas iniciales - tamaño player)
	d.line = mlx_new_image(d.mlx, 75, 75);
	ft_draw_line(d.line, 38, 38, 75, 38, 1); //x0,y0 = centro de la imagen (x / 2 + 1, y / 2 + 1). x1 = borde derecho (75), y1 = y0 (linea horizontal)
	mlx_image_to_window(d.mlx, d.line, 175, 175);
	
	//hooks a eventos 
	mlx_loop_hook(d.mlx, ft_hook, &d);
	mlx_loop(d.mlx);
	mlx_terminate(d.mlx);

	return (EXIT_SUCCESS);
}
*/