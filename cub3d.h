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
#include <limits.h>
#include "MLX42/include/MLX42/MLX42.h"
#include <unistd.h>
#include "libft/libft.h"

#define WIDTH 800 // x
#define HEIGHT 600 // y
#define TILE_SIZE 100 //tamaño de cada casilla ya sea x_side o y_side (SON CUADRADAS)
#define FOV 60

typedef struct s_data_player
{
	int advance; 
	int turn_on;
	int next_y; //no asignada aun
	int next_x; //no asignada aun
	double wall_hit_x;
	double wall_hit_y;
	double wall_hit_x_horizontal;
	double wall_hit_y_horizontal;
	double wall_hit_x_vertical;
	double wall_hit_y_vertical;
	double speed_advance; 
	double speed_turn_on;
	double angle_rotation; //en radianes
	double y_intercept;
	double x_intercept;
	double x;
	double y;
	bool west;
	bool south;

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
	char **map;

}	t_data;

int get_rgba(int r, int g, int b, int a);

void ft_draw_player(void *data);

void ft_draw_square(mlx_image_t *image, int x_limit, int y_limit, int color);

void ft_draw_line(mlx_image_t* image, int x0, int y0, int x1, int y1, int mode);

void ft_draw_map(void *data);

void ft_draw_ray(void *param);

double ft_horizontal_collision(t_data *d);

double ft_vertical_collision(t_data *d);

int collider_checker(t_data *d, double x, double y);