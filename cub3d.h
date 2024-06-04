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

#define WIDTH 1600 // x
#define HEIGHT 1200 // y
#define TILE_SIZE 64 //tamaño de cada casilla ya sea x_side o y_side (SON CUADRADAS)

typedef struct s_data
{
    mlx_t   *mlx;
    char    **map;
}   t_data;


int ft_parse_input(int argc, char **argv, t_data *d);