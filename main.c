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

	//implementacion de los hooks con datos como 1 o -1, para multiplicar por la velocidad de steps o speed_avance / speed_turn_on
	if (mlx_is_key_down(d->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(d->mlx);
	if (mlx_is_key_down(d->mlx, MLX_KEY_W) == true)
		*(d->data_player->advance) += 1;
	if (mlx_is_key_down(d->mlx, MLX_KEY_S) == true)
		*(d->data_player->advance) -= 1;
	if (mlx_is_key_down(d->mlx, MLX_KEY_D) == true)
		*(d->data_player->turn_on) += 1;
	if (mlx_is_key_down(d->mlx, MLX_KEY_A) == true)
		*(d->data_player->turn_on) -= 1;
	ft_draw_player(param);
	//hola ales, esto es setear los valores a 0 cuando ya se han pulsado, es mi implementacion del hook_key_release
	if (*(d->data_player->advance) != 0)
		*(d->data_player->advance) = 0;
	if (*(d->data_player->turn_on) != 0)
		*(d->data_player->turn_on) = 0;
}

int main(void)
{
	t_data	*d = malloc(sizeof(t_data));
	//he añadido una serie de datos relevantes al player, que necesito pasar por referencia y alojar dinamicamente.
	//por eso hago malloc, con el onjetivo de poder modificarlos des de otras funciones
	d->data_player = malloc(sizeof(t_data_player));
	d->data_player->advance =  malloc(sizeof(int));
	*(d->data_player->advance) =  0;
	d->data_player->turn_on =  malloc(sizeof(int));
	*(d->data_player->turn_on) =  0;
	d->data_player->angle_rotation = malloc(sizeof(double));
	*(d->data_player->angle_rotation) = 0.0;
	d->data_player->speed_advance = malloc(sizeof(double));
	*(d->data_player->speed_advance) = 3.0;
	d->data_player->speed_turn_on = malloc(sizeof(double));
	*(d->data_player->speed_turn_on) = 3.0 * (M_PI / 180.0);
	//carga la ventana
	d->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", true);

	//new_image define una imagen con sus tamaños y el ptr a la ventana, despues se dibuja con draw_square
	d->square_b = mlx_new_image(d->mlx, 100, 100);
	ft_draw_square(d->square_b, 100, 100, 1);
	d->square_w = mlx_new_image(d->mlx, 100, 100);
	ft_draw_square(d->square_w, 100, 100, 2);
	//se dibuja el mapa solo una vez
	ft_draw_map(d);

	//dibuja el jugador en las coordenadas iniciales (200,200)
	d->player = mlx_new_image(d->mlx, 25, 25);
	ft_draw_square(d->player, 25, 25, 3);
	mlx_image_to_window(d->mlx, d->player, 200, 200);

	//dibuja la imagen de la linea en direccion 0 radianes y coordenadas para que el centro coincida con el player (coordenadas iniciales - tamaño player)
	d->line = mlx_new_image(d->mlx, 75, 75);
	ft_draw_line(d->line, 38, 38, 75, 38); //x0,y0 = centro de la imagen (x / 2 + 1, y / 2 + 1). x1 = borde derecho (75), y1 = y0 (linea horizontal)
	mlx_image_to_window(d->mlx, d->line, 175, 175);

	//TEST STRING
	mlx_image_t *text = mlx_put_string(d->mlx, "test text", 0, 0); //para testear como poner strings en pantalla
	mlx_set_instance_depth(text->instances, 50); //para modificar la intensidad con la que se ve la string
	mlx_image_to_window(d->mlx, text, 0, 0); //string cargada en la pantalla

	

	//hooks a eventos 
	mlx_loop_hook(d->mlx, ft_hook, d);
	mlx_loop(d->mlx);
	mlx_terminate(d->mlx);
	free(d->data_player->advance);
	free(d->data_player->turn_on);
	free(d->data_player->speed_advance);
	free(d->data_player->speed_turn_on);
	free(d->data_player->angle_rotation);
	free(d->data_player);
	free(d);
	return (EXIT_SUCCESS);
}
