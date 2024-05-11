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

typedef struct s_data_player
{
	int *advance;  //0 1 -1
	int *turn_on; //0 1 -1
	double *speed_advance; //3
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

int get_rgba(int r, int g, int b, int a);

void ft_draw_player(void *data);

void ft_draw_square(mlx_image_t *image, int x_limit, int y_limit, int color);

void ft_draw_map(void *data);