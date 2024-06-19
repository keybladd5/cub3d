/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 17:48:15 by polmarti          #+#    #+#             */
/*   Updated: 2024/06/15 17:48:17 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * Normalizes an angle to ensure that it is always in the range 0 to 2π 
 * radians.
 * If the angle is negative, 2π is added to bring it within the range.
 * If the angle is greater than 2π, 2π is subtracted to bring it within 
 * the range.
 *
 * @param angle The angle to be normalized, in radians.
 * @return The normalized angle, in the range [0, 2π) radians.
 */
double	ft_nor_angle(double angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

/**
 * @brief Deallocates memory associated with the map structure.
 *
 * This function frees the memory allocated for a map (`map`) 
 * structure. It performs
 * the following tasks:
 *
 * - Frees textures associated with north, south, west, 
 *   and east walls (if allocated).
 * - Frees each individual row within the map array 
 *   (`map->map`) using `free`.
 * - Frees the entire map array itself using `free`.
 *
 * @param map Pointer to the map structure to be freed.
 */
void	ft_free_map(t_map *map)
{
	int	i;

	if (map->tex.no)
		mlx_delete_texture(map->tex.no);
	if (map->tex.so)
		mlx_delete_texture(map->tex.so);
	if (map->tex.we)
		mlx_delete_texture(map->tex.we);
	if (map->tex.ea)
		mlx_delete_texture(map->tex.ea);
	if (map->map)
	{
		i = 0;
		while (map->map[i])
		{
			free (map->map[i]);
			i++;
		}
		free(map->map);
	}
}

/**
 * @brief In-place search and replace in a string.
 *
 * This function modifies the provided string (`str`) 
 * by replacing all occurrences
 * of the character `og` with the character `new`. It performs an in-place
 * modification, directly changing the contents of the `str` array.
 *
 * @param str String to be modified.
 * @param og Character to be replaced.
 * @param new Character to replace with.
 */
void	ft_search_replace(char *str, char og, char new)
{
	int	len;

	len = ft_strlen(str);
	while (--len)
	{
		if (str[len] == og)
			str[len] = new;
	}
}

/**
 * @brief Skips leading whitespace (excluding newline).
 *
 * @param str String to skip leading whitespace from.
 * @return Pointer to first non-whitespace character.
 */
char	*ft_skip_spaces(char *str)
{
	while (ft_isspace(*str) && *str != '\n')
		str++;
	return (str);
}
