/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:39:35 by polmarti          #+#    #+#             */
/*   Updated: 2024/06/16 18:39:38 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Selects and returns the appropriate texture for 
 * rendering walls based on the direction
 * indicated by the flag. If flag is 0, selects 
 * between east and west textures; if flag is 1,
 * selects between south and north textures.
 *
 * @param d Pointer to the main data structure containing
 *  scene and graphics information.
 * @param flag Flag indicating the direction of the wall 
 * texture to select (0 for east/west, 1 for south/north).
 * @return Pointer to the selected texture.
 */
mlx_texture_t	*get_texture_walls(t_data *d, int flag)
{
	if (flag == 0)
	{
		if (d->data_player.west == true)
			return (d->map.tex.we);
		else
			return (d->map.tex.ea);
	}
	else
	{
		if (d->data_player.south == true)
			return (d->map.tex.so);
		else
			return (d->map.tex.no);
	}
}

mlx_texture_t	*ft_load_texture(char *line)
{
	mlx_texture_t	*p_tex;

	line += 2;
	while (ft_isspace(*line) && *line != '\n')
		line++;
	ft_search_replace(line, '\n', '\0');
	p_tex = mlx_load_png(line);
	if (!p_tex)
		return (ft_putstr_fd("Error\nUnable to open texture asset\n", 2), NULL);
	return (p_tex);
}

int	ft_read_texture(t_map *map, char *line)
{
	if (!ft_strncmp(line, "NO", 2))
	{
		map->tex.no = ft_load_texture(line);
		if (!map->tex.no)
			return (1);
	}
	else if (!ft_strncmp(line, "SO", 2))
	{
		map->tex.so = ft_load_texture(line);
		if (!map->tex.so)
			return (1);
	}
	else if (!ft_strncmp(line, "WE", 2))
	{
		map->tex.we = ft_load_texture(line);
		if (!map->tex.we)
			return (1);
	}
	else if (!ft_strncmp(line, "EA", 2))
	{
		map->tex.ea = ft_load_texture(line);
		if (!map->tex.ea)
			return (1);
	}
	return (0);
}
