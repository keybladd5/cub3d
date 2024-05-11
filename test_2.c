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
#include <math.h>
#include "colors.h"
#include "MLX42/include/MLX42/MLX42.h"

#define WIDTH 800 // x
#define HEIGHT 600 // y

typedef struct s_data_player
{
	int *advance;
	int *turn_on;
	double *speed_advance;
	double *speed_turn_on;
	double *angle_rotation;
} t_data_player;

typedef struct s_data
{
	mlx_t* mlx;
	mlx_image_t  *square_b;
	mlx_image_t  *square_w;
	mlx_image_t	 *player;
	t_data_player *data_player;

}	t_data;

//funcion para obtener el color al llamar a put_pixel
//si se llama a esta funcion con a en 0, hace el color completamente trnasparente, si se hace con 255, sin transparencia
int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}


//esta funcion modifica la instancia de la imagen, con los datos del player a traves de los calculos trigonometricos 
void ft_draw_player(void *data)
{
	t_data *d = data;
	double new_x;
	double new_y;
	char map[7][9] = {
    {'1', '1', '1', '1', '1', '1', '1', '1', '\0'},
    {'1', '0', '0', '0', '0', '0', '0', '1', '\0'},
    {'1', '0', '0', '0', '0', '0', '0', '1', '\0'},
    {'1', '0', '0', '0', '0', '0', '0', '1', '\0'},
	{'1', '0', '0', '0', '0', '0', '0', '1', '\0'},
    {'1', '1', '1', '1', '1', '1', '1', '1', '\0'},
    };

	//prevision de calculo de a donde se va a desplazar el player
	new_x =  (double)d->player->instances[0].x + (d->data_player->advance[0] * cos(d->data_player->angle_rotation[0]) * d->data_player->speed_advance[0]); 
	new_y =  (double)d->player->instances[0].y + (d->data_player->advance[0] * sin(d->data_player->angle_rotation[0]) * d->data_player->speed_advance[0]);
	printf("new_x = %f new_y = %f radians = %f \n", new_x, new_y, *(d->data_player)->angle_rotation);//print de informacion x terminal

	//asignacion de la direccion del player, en radianes
	*(d->data_player)->angle_rotation += (*(d->data_player)->turn_on * *(d->data_player)->speed_turn_on);
	if (*(d->data_player)->angle_rotation >= (2 * M_PI)) //para que no pase los radians del maximo en grados 
		*(d->data_player)->angle_rotation = 0.0;
	if (*(d->data_player)->angle_rotation < 0.0) //para que no pase a radianes negativos y conectar ambos limites
		*(d->data_player)->angle_rotation = (2 * M_PI);
	
	//checkeo de colisiones
	if (map[(int)round(new_y) / 100][(int)round(new_x) / 100] == '0')//para imlementar la colision con los limites des de el primer punto dibujado del player
	{
		d->player->instances[0].x = round(new_x);//round =  funcion para redondear el dato double a integer
		d->player->instances[0].y = round(new_y);
	}
	printf("x = %d y = %d \n", d->player->instances[0].x,  d->player->instances[0].y);//print de informacion de la posicion en pixels del cuadrado
}

void ft_hook(void* param)
{
	t_data *d = param;

	//implementacion de los hooks con datos como 1 o -1, para multiplicar por la velocidad de steps o speed_avance / speed_turn_on
	if (mlx_is_key_down(d->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(d->mlx);
	else if (mlx_is_key_down(d->mlx, MLX_KEY_W) == true)
		*(d->data_player->advance) = 1;
	else if (mlx_is_key_down(d->mlx, MLX_KEY_S) == true)
		*(d->data_player->advance) = -1;
	else if (mlx_is_key_down(d->mlx, MLX_KEY_D) == true)
		*(d->data_player->turn_on) = 1;
	else if (mlx_is_key_down(d->mlx, MLX_KEY_A) == true)
		*(d->data_player->turn_on) = -1;
	ft_draw_player(param);
	//hola ales, esto es setear los valores a 0 cuando ya se han pulsado, es mi implementacion del hook_key_release
	if (*(d->data_player->advance) != 0)
		*(d->data_player->advance) = 0;
	else if (*(d->data_player->turn_on) != 0)
		*(d->data_player->turn_on) = 0;
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
	//ft_draw_player(d->mlx, d->player, 200, 200);
	ft_draw_square(d->player, 20, 20, 3);
	mlx_image_to_window(d->mlx, d->player, 200, 200);
}
int main(void)
{
	t_data	*d;
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

	//new_image define una imagen con sus tamaños y el ptr a la ventana, despues se dibuja con draw_square
	d->square_w = mlx_new_image(d->mlx, 100, 100);
	ft_draw_square(d->square_w, 100, 100, 2);

	d->player = mlx_new_image(d->mlx, 30, 20);

	ft_draw_map(d);
	mlx_loop_hook(d->mlx, ft_hook, d);
	mlx_loop(d->mlx);
	mlx_terminate(d->mlx);
	return (EXIT_SUCCESS);
}
