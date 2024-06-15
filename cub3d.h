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

#define WIDTH 1920 // x
#define HEIGHT 1080 // y
#define TILE_SIZE 64 //tamaño de cada casilla ya sea x_side o y_side (SON CUADRADAS)

typedef struct s_map
{
    mlx_texture_t	*no;
	mlx_texture_t   *so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
    uint32_t		f_color;
    uint32_t		c_color;
    int				spawn;
    char    		**map;
}   t_map;

typedef struct s_data
{
    mlx_t   *mlx;
    t_map   map;

    mlx_image_t *background;

}   t_data;


int ft_parse_input(int argc, char **argv, t_map *map);

int get_rgba(int r, int g, int b, int a);

void    ft_free_map(t_map *map);

void	ft_search_replace(char *str, char og, char new);

int	ft_load_mapdata(t_map *map, char *line);