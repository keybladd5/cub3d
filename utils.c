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

//libera el mapa
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

char	*ft_skip_spaces(char *str)
{
	while (ft_isspace(*str) && *str != '\n')
		str++;
	return (str);
}

int	ft_error(int type)
{
	ft_putstr_fd("Error\n", 2);
	if (type == ERROR_ARG)
		ft_putstr_fd("Wrong argument correct format is ./cub3d file.cub\n", 2);
	else if (type == ERROR_OPEN)
		ft_putstr_fd("Unable to open specified scene file\n", 2);
	else if (type == ERROR_TEX_BG)
		ft_putstr_fd("Missing texture/background data\n", 2);
	else if (type == ERROR_EMPTY_LINE)
		ft_putstr_fd("Empty line found in map\n", 2);
	else if (type == ERROR_CHAR)
		ft_putstr_fd("Unexpected character found in map\n", 2);
	else if (type == ERROR_SPAWN)
		ft_putstr_fd("Multiple spawn points found in map\n", 2);
	else if (type == ERROR_NO_SPAWN)
		ft_putstr_fd("Unexpected character found in map\n", 2);
	else if (type == ERROR_MAP_SURROUND)
		ft_putstr_fd("Map not fully enclosed\n", 2);
	else if (type == ERROR_DATA)
		ft_putstr_fd("Unexpeced data found in scene file\n", 2);
	else if (type == ERROR_DUP_DATA)
		ft_putstr_fd("Duplicate scene data found\n", 2);
	else if (type == ERROR_RGBA)
		ft_putstr_fd("Wrong color format must be R,G,B in range[0,255]\n", 2);
	return (1);
}
