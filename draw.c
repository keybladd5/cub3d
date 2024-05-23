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

char g_map[7][9] = {
    {'1', '1', '1', '1', '1', '1', '1', '1', '\0'},
    {'1', '0', '0', '0', '0', '0', '0', '1', '\0'},
    {'1', '0', '0', '1', '1', '1', '0', '1', '\0'},
    {'1', '0', '0', '1', '0', '0', '0', '1', '\0'},
	{'1', '0', '0', '0', '0', '0', '0', '1', '\0'},
    {'1', '1', '1', '1', '1', '1', '1', '1', '\0'},
    };

// Función para dibujar una línea entre dos puntos en una imagen
void ft_draw_line(mlx_image_t* image, int x0, int y0, int x1, int y1, int mode) 
{
    int dx = (int)fabs((double)(x1 - x0));
    int dy = (int)fabs((double)(y1 - y0));
	//printf("dx = %d, dy = %d\n", dx, dy);
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
		if (mode == 1)
       		mlx_put_pixel(image, x0, y0, get_rgba(255, 255, 255, 255)); // Dibuja el pixel en la posición (x0, y0)
		else
			mlx_put_pixel(image, x0, y0, get_rgba(255, 0, 0, 255));
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
		if (x0 >= WIDTH || y0 >= HEIGHT)
			break ;
    }
}

void ft_draw_ray(void *param)
{
	t_data *d = param;
	double x_collision = ft_horizontal_collision(d);
	double y_collision = ft_vertical_collision(d);

	printf(" x_c -> %f y_c -> %f\n", x_collision, y_collision);
	if (x_collision < y_collision)
	{
		d->data_player.wall_hit_x = d->data_player.wall_hit_x_horizontal;
		d->data_player.wall_hit_y =  d->data_player.wall_hit_y_horizontal;
		printf("x_c WIN\n");
	}
	else if (x_collision == y_collision)
		printf("EQUALS\n");
	else
	{
		d->data_player.wall_hit_x = d->data_player.wall_hit_x_vertical;
		d->data_player.wall_hit_y =  d->data_player.wall_hit_y_vertical;
		printf("x_y WIN\n");
	}
	printf("x0: %d, y0: %d, x1: %d, y1: %d\n", d->player->instances[0].x + 12, d->player->instances[0].y + 12, d->data_player.wall_hit_x, d->data_player.wall_hit_y);
	mlx_delete_image(d->mlx, d->rays);
	d->rays = mlx_new_image(d->mlx, WIDTH, HEIGHT);
	ft_draw_line(d->rays, d->player->instances[0].x + 12, d->player->instances[0].y + 12,  d->data_player.wall_hit_x, d->data_player.wall_hit_y, 2);
	mlx_image_to_window(d->mlx, d->rays, 0, 0);

	

}

//esta funcion modifica la instancia de la imagen, con los datos del player a traves de los calculos trigonometricos 
void ft_draw_player(void *data)
{
	t_data *d = data;
	double new_x;
	double new_y;
	d->data_player.south = false;
	d->data_player.west = false;

	//prevision de calculo de a donde se va a desplazar el player
	new_x =  (double)d->player->instances[0].x + (d->data_player.advance * cos(d->data_player.angle_rotation) * d->data_player.speed_advance); 
	new_y =  (double)d->player->instances[0].y + (d->data_player.advance * sin(d->data_player.angle_rotation) * d->data_player.speed_advance);
	//printf("new_x = %f new_y = %f radians = %f \n", new_x, new_y, d->data_player.angle_rotation);//print de informacion x terminal

	//asignacion de la direccion del player, en radianes
	d->data_player.angle_rotation += (d->data_player.turn_on * d->data_player.speed_turn_on);
	if (d->data_player.angle_rotation <= 0.0) //para que no pase a radianes negativos y conectar ambos limites
		d->data_player.angle_rotation += (2 * M_PI);
	if (d->data_player.angle_rotation >= (2 * M_PI)) //para que no pase los radians del maximo en grados 
		d->data_player.angle_rotation -= (2 * M_PI);
	
	//asignacion de variable south y west
	if (d->data_player.angle_rotation < M_PI)
		d->data_player.south = true;

	if (d->data_player.angle_rotation > (M_PI/2) && d->data_player.angle_rotation < (3 * M_PI/2))
		d->data_player.west = true;

	//checkeo de colisiones
	if (g_map[(int)round(new_y + 12.0) / 100][(int)round(new_x + 12.0) / 100] == '0')//para imlementar la colision con los limites des de el primer punto dibujado del player
	{
		d->player->instances[0].x = round(new_x);//round =  funcion para redondear el dato double a integer
		d->player->instances[0].y = round(new_y);
	}
	
	//redibujar linea en la direccion del player si hay rotacion
	/*if (d->data_player.turn_on != 0)
	{
		//borra la imagen y crea otra imagen del mismo tamaño
		mlx_delete_image(d->mlx, d->line);
		d->line = mlx_new_image(d->mlx, 75, 75);
		//dibuja la nueva linea segun el nuevo angulo. x0,y0 se mantiene en el centro, x1,y1 = catetos del triangulo rectangulo que tiene como hipotenusa la propia linea con origen en el centro del player y angulo angle_rotation
		ft_draw_line(d->line, 38, 38, 38 + (37 * cos(d->data_player.angle_rotation)), 38 + (37 * sin(d->data_player.angle_rotation)), 1);
		mlx_image_to_window(d->mlx, d->line, round(new_x - 25), round(new_y - 25));
	}*/
	//si no hay rotacion, mueve la linea igual que el player
	/*else
	{
		d->line->instances[0].x = round(new_x - 25);
		d->line->instances[0].y = round(new_y - 25);
	}*/
	

	printf("x = %d y = %d  radians = %f\n", d->player->instances[0].x,  d->player->instances[0].y, d->data_player.angle_rotation);//print de informacion de la posicion en pixels del cuadrado
	printf("speed = %d west = %d south = %d\n", d->data_player.advance, d->data_player.west, d->data_player.south);
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

	int y = 0;
	int x = 0;
	//buncle que renderiza la imagen de la ventana una vez 
	while (y < 6)
	{
		x = 0;
		while (x < 8)
		{
			if (g_map[y][x] == '1')
			{
				mlx_image_to_window(d->mlx, d->square_b, (x * 100), (y * 100));
			}
			else if (g_map[y][x] == '0')
			{
				mlx_image_to_window(d->mlx, d->square_w, (x * 100), (y *  100));
			}
			x++;
		}
		y++;
	}
}
