/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 13:52:57 by polmarti          #+#    #+#             */
/*   Updated: 2024/05/11 13:52:59 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Función para dibujar una línea entre dos puntos en una imagen
void ft_draw_line(mlx_image_t* image, int x0, int y0, int x1, int y1, int color) 
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx, sy;

    if (x0 < x1)
		sx = 1;
    else
		sx = -1;
    if (y0 < y1)
		sy = 1;
	else
		sy = -1;

    int err = dx - dy;

    while (x0 != x1 || y0 != y1) 
	{
        mlx_put_pixel(image, x0, y0, get_rgba(255, 255, 255, 255)); // Dibuja el pixel en la posición (x0, y0)

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
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
		*(d->data_player)->angle_rotation -= (2 * M_PI);
	if (*(d->data_player)->angle_rotation < 0.0) //para que no pase a radianes negativos y conectar ambos limites
		*(d->data_player)->angle_rotation += (2 * M_PI);
	//ft_draw_line()
	//checkeo de colisiones
	if (map[(int)round(new_y) / 100][(int)round(new_x) / 100] == '0')//para imlementar la colision con los limites des de el primer punto dibujado del player
	{
		d->player->instances[0].x = round(new_x);//round =  funcion para redondear el dato double a integer
		d->player->instances[0].y = round(new_y);
	}
	printf("x = %d y = %d  degrees = %f\n", d->player->instances[0].x,  d->player->instances[0].y, *(d->data_player)->angle_rotation *  (180/M_PI));//print de informacion de la posicion en pixels del cuadrado
	printf("speed = %d\n", *(d->data_player->advance));
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
			//sleep(100);
		}
		//printf("\n");
		y++;
	}
	//ft_draw_player(d->mlx, d->player, 200, 200);
	ft_draw_square(d->player, 20, 20, 3);
	mlx_image_to_window(d->mlx, d->player, 200, 200);
}
