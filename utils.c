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
 * Reverses the bytes of a 32-bit integer.
 * Takes an integer and swaps its bytes to convert between 
 * little-endian and big-endian formats.
 *
 * @param c The 32-bit integer whose bytes are to be reversed.
 * @return The 32-bit integer with its bytes reversed.
 */
int	reverse_bytes(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}

//libera el mapa
void    ft_free_map(t_map *map)
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
