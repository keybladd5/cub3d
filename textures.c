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
mlx_texture_t	*get_texture_walls(t_data *d, int collission)
{
	if (collission == VERTICAL)
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

/**
 * @brief Loads a texture file and performs basic validation.
 *
 * Skips leading whitespace, removes trailing newline, 
 * loads the texture using * `mlx_load_png`, and checks for 
 * successful loading and dimensions (64x64).
 * Returns the texture pointer on success, 
 * or NULL with error message on failure.
 *
 * @param line String containing the path to the texture file.
 *
 * @return Pointer to the loaded texture (mlx_texture_t) or NULL on error.
 */
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
	if (p_tex->height != 64 || p_tex->width != 64)
		return (ft_putstr_fd("Error\nTextures must be 64x64 pixel\n", 2), NULL);
	return (p_tex);
}

/**
 * @brief Assigns loaded texture based on identifier (NO, SO, WE, EA)
 *
 * Reads texture identifier (first 2 characters) and assigns loaded texture
 * from `ft_load_texture` to corresponding member in `map->tex`. 
 * Returns 1 on error, * 0 on success.
 *
 * @param map Pointer to the map structure.
 * @param line String containing texture identifier and path.
 *
 * @return 0 on success, 1 on error (loading or invalid identifier).
 */
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
