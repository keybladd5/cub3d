/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:52:10 by polmarti          #+#    #+#             */
/*   Updated: 2024/05/07 11:52:12 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "MLX42/include/MLX42/MLX42.h"
#include <unistd.h>

#define WIDTH 800 // x
#define HEIGHT 600 // y
#define TILE_SIZE 100 //tamaño de cada casilla ya sea x_side o y_side (SON CUADRADAS)

typedef struct s_data_player
{
	int advance; 
	int turn_on;
	int y_intercept;
	int x_intercept;
	int next_y; //no asignada aun
	int next_x; //no asignada aun
	int wall_hit_x;
	int wall_hit_y;
	bool west;
	bool south;
	bool x_impact;
	bool y_impact;
	double speed_advance; 
	double speed_turn_on;
	double angle_rotation; //en radianes

} t_data_player;

typedef struct s_data
{
	mlx_t* mlx;
	mlx_image_t		*square_b;
	mlx_image_t		*square_w;
	mlx_image_t		*player;
	mlx_image_t		*line;
	mlx_image_t		*rays;
	t_data_player	data_player;

}	t_data;

int get_rgba(int r, int g, int b, int a);

void ft_draw_player(void *data);

void ft_draw_square(mlx_image_t *image, int x_limit, int y_limit, int color);

void ft_draw_line(mlx_image_t* image, int x0, int y0, int x1, int y1);

void ft_draw_map(void *data);

void ft_draw_ray(void *param);