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

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <limits.h>
# include "MLX42/include/MLX42/MLX42.h"
# include <unistd.h>
# include "libft/libft.h"
# define WIDTH				1920
# define HEIGHT				1080
# define TILE_SIZE			64
# define LATERAL_RADIANS	1.570796326794897
# define FOV				60
# define M_PI				3.14159265358979323846
# define ERROR_ARG			5
# define ERROR_OPEN			6
# define ERROR_TEX_BG		7
# define ERROR_NL			8
# define ERROR_CHAR			9
# define ERROR_SPAWN		10
# define ERROR_NO_SPAWN		11
# define ERROR_MAP_SURROUND	12
# define ERROR_DATA			13
# define ERROR_DUP_DATA		14
# define ERROR_RGBA			15
# define HORIZONTAL			16
# define VERTICAL			17

typedef uint32_t	t_32;

typedef struct s_data_player
{
	int		advance;
	int		turn_on;
	double	speed_advance;
	double	speed_turn_on;
	double	angle_rotation; //en radianes
	int		lateral_move;
	int		x;
	int		y;
	float	fov_radians;
	bool	west;
	bool	south;

}	t_data_player;

typedef struct s_minimap
{
	int	x;
	int	y;
	int	x_limit;
	int	y_limit;
	int	tile_size;
}	t_minimap;

typedef struct s_rays
{
	int		collission;//if horizontal collision is the lower 1, else 0
	int		index;//index of rays
	double	wall_hit_x_horizontal;
	double	wall_hit_y_horizontal;
	double	wall_hit_x_vertical;
	double	wall_hit_y_vertical;	
	double	ray_ngl;//angle of ray
	double	distance;//beteen 2 impacts x and y
}	t_rays;

typedef struct s_textures
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
	unsigned int	*arr;
}	t_textures;

typedef struct s_dda_data
{
	double	dda_x;
	double	dda_y;
	double	x_step;
	double	y_step;
	int		pixel;
}	t_dda_data;

typedef struct s_map
{
	t_textures	tex;
	uint32_t	f_color;
	uint32_t	c_color;
	int			spawn;
	int			spawn_x; //old map_x
	int			spawn_y; //old map_y
	int			size_x;//tamaño del mapa
	int			size_y;//tamaño del mapa
	char		**map;
}	t_map;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	mlx_image_t		*n_image;
	t_data_player	data_player;
	t_rays			cast_rays;
	t_minimap		minimap;
	t_map			map;
}	t_data;

/*****<MAIN>*****/

int				get_rgba(int r, int g, int b, int a);

int				collider_checker(t_data *d, double x, double y);

void			ft_render_scene(t_data *d);

double			nor_angle(double angle);

void			draw_floor_ceiling(t_data *d, int ray, int t_pix, int b_pix);

int				color_walls(t_data *d, int flag);

mlx_texture_t	*get_texture_walls(t_data *d, int flag);

void			ft_ray_caster(t_data *d, int ray);

void			ft_movement_hook(t_data *d);

void			ft_move_player(t_data *d);

void			ft_free_map(t_map *map);

void			safe_pixel_put(mlx_image_t *image, int x, int y, int color);

double			get_h_inter(t_data *d, double angl);

double			get_v_inter(t_data *d, double angl);

void			check_side(t_data *d, double angle);

void			draw_wall_texture(t_data *d, int t_pix, int b_pix, \
double wall_h);

int				reverse_bytes(int c);

void			ft_draw_minimap(t_data *d, int y, int x);

void			ft_draw_square(mlx_image_t *image, t_minimap *map, int color);

void			ft_esc(void *param);

int				ft_parse_input(int argc, char **argv, t_map *map);

int				ft_load_mapdata(t_map *map, char *line);

void			ft_search_replace(char *str, char og, char new);

char			*ft_skip_spaces(char *str);

int				ft_read_texture(t_map *map, char *line);

int				ft_parse_mapdata(char **line, int scenefd, t_map *map);

int				ft_parse_map(char **line, int scenefd, t_map *map);

void			init_data_map(t_data *d);

void			init_data_player(t_data *d);

int				ft_parse_error(int type);

#endif