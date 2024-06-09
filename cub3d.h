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
#include "MLX42/include/MLX42/MLX42.h"
#include <unistd.h>
#include "libft/libft.h"

# define WIDTH 	1920 // x
# define HEIGHT 1080 // y
# define TILE_SIZE 64 //tamaño de cada casilla ya sea x_side o y_side (SON CUADRADAS)
# define MINIMAP_TILE_SIZE 15
# define LATERAL_RADIANS 1.570796326794897
# define FOV 60
# define M_PI		3.14159265358979323846	/* pi */
typedef struct s_data_player
{
	int advance; 
	int turn_on;
	double speed_advance; 
	double speed_turn_on;
	double angle_rotation; //en radianes
	int lateral_move;
	int x;
	int y;
	float fov_radians;
	bool west;
	bool south;

} t_data_player;

typedef struct s_minimap
{
	int				heigt;
	int				width;
	int				x;
	int				y;
	int 			x_limit;
	int 			y_limit;
	mlx_image_t		*map;

}	t_minimap;

typedef struct s_rays
{
	int flag;//if horizontal collision is the lower 1, else 0
	int index;
	double wall_hit_x_horizontal;
	double wall_hit_y_horizontal;
	double wall_hit_x_vertical;
	double wall_hit_y_vertical;	
	double y_intercept;
	double x_intercept;
	double ray_ngl;
	double distance;

}	t_rays;

typedef struct s_textures
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
}	t_textures;

typedef struct s_data
{
	mlx_t* mlx;
	mlx_image_t		*image;
	t_data_player	data_player;
	t_rays			cast_rays;
	t_textures		tex;
	t_minimap		minmap;
	char 			**map;
	int				map_x;
	int				map_y;
	int				size_x;//tamaño del mapa
	int				size_y;//tamaño del mapa

}	t_data;

int		get_rgba(int r, int g, int b, int a);

int		collider_checker(t_data *d, double x, double y);

void	ft_cast_rays(t_data *d);

double	nor_angle(double angle);

void	draw_floor_ceiling(t_data *d, int ray, int t_pix, int b_pix);

int		color_walls(t_data *d, int flag);

mlx_texture_t *get_texture_walls(t_data *d, int flag);

void	render_walls(t_data *d, int ray);

void	ft_movement_hook(void *d);

void	ft_move_player(t_data *d);

void	ft_free_map(char **map);

void	safe_pixel_put(mlx_image_t *image, int x, int y, int color);

double	get_h_inter(t_data *d, double angl);

double	get_v_inter(t_data *d, double angl);

void	check_side(t_data *d, double angle);

void	ft_get_size_map(t_data *d, char **map);

void	ft_mlx_error(void);

void	draw_wall_texture(t_data *d, int t_pix, int b_pix, double wall_h);

int	reverse_bytes(int c);

void ft_draw_minimap(t_data *d);

void ft_draw_square(mlx_image_t *image, t_minimap *map,  int color);