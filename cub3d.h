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
	double speed_advance; 
	double speed_turn_on;
	double angle_rotation; //en radianes
	int x;
	int y;
	double fov_radians;
	bool west;
	bool south;

} t_data_player;

typedef struct s_rays
{
	int next_y; //no asignada aun
	int next_x; //no asignada aun
	int flag;
	double wall_hit_x_horizontal;
	double wall_hit_y_horizontal;
	double wall_hit_x_vertical;
	double wall_hit_y_vertical;	
	double y_intercept;
	double x_intercept;
	double ray_ngl;
	double distance;

}	t_rays;

typedef struct s_data
{
	mlx_t* mlx;
	mlx_image_t		*square_b;
	mlx_image_t		*square_w;
	mlx_image_t		*player;
	mlx_image_t		*line;
	mlx_image_t		*image;
	t_data_player	data_player;
	t_rays			cast_rays;
	char 			**map;

}	t_data;

int get_rgba(int r, int g, int b, int a);

void ft_draw_player(void *data);

void ft_draw_square(mlx_image_t *image, int x_limit, int y_limit, int color);

void ft_draw_line(mlx_image_t* image, int x0, int y0, int x1, int y1, int mode);

void ft_draw_map(void *data);

void ft_draw_ray(void *param);

double ft_horizontal_collision(t_data *d, double angle);

double ft_vertical_collision(t_data *d, double angle);

int collider_checker(t_data *d, double x, double y);

void ft_cast_rays(t_data *d);

double nor_angle(double angle);

void	draw_floor_ceiling(t_data *d, int ray, int t_pix, int b_pix);

void	draw_wall(t_data *d, int ray, int t_pix, int b_pix);

int color_walls(t_data *d, int flag);

void render_walls(t_data *d, int ray);

void ft_movement_hook(void *d);

void ft_move_player(t_data *d);

void ft_free_map(char **map);

void safe_pixel_put(mlx_image_t *image, int x, int y, int color);

double	get_h_inter(t_data *d, double angl);

int	inter_check(double angle, double *inter, double *step, int is_horizon);

int	unit_circle(double angle, char c);

double	get_v_inter(t_data *d, double angl);

void change_map_position(t_data *d);