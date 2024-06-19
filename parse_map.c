/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-tole <ade-tole@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 19:05:47 by ade-tole          #+#    #+#             */
/*   Updated: 2024/06/16 19:06:01 by ade-tole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Validates map characters and ensures single spawn point.
 * @param map_str Map string
 * @param map Map structure
 * @return 0 on success, error code otherwise
 */
int	ft_check_mapchars(char *map_str, t_map *map)
{
	int	i;

	i = 0;
	while (map_str[i])
	{
		if (map_str[i] == 'N' || map_str[i] == 'S' \
		|| map_str[i] == 'W' || map_str[i] == 'E')
		{
			if (map->spawn)
				return (ft_parse_error(ERROR_SPAWN));
			else
				map->spawn = map_str[i];
		}
		else if (map_str[i] != '1' && map_str[i] != '0' && \
		map_str[i] != ' ' && map_str[i] != '\n')
			return (ft_parse_error(ERROR_CHAR));
		i++;
	}
	if (!map->spawn)
		return (ft_parse_error(ERROR_NO_SPAWN));
	return (0);
}

/**
 * @brief Checks if a tile is open (not surrounded by walls).
 * @param map Map structure
 * @param i X-coord
 * @param j Y-coord
 * @return 1 if open, 0 otherwise
 */
int	ft_tile_notclosed(t_map *map, int i, int j)
{
	if ((!map->map[i][j - 1] || map->map[i][j - 1] == ' ') || \
	(!map->map[i][j + 1] || map->map[i][j + 1] == ' ') || \
	(j >= (int)ft_strlen(map->map[i - 1]) || map->map[i - 1][j] == ' ') \
	|| (j >= (int)ft_strlen(map->map[i + 1]) || map->map[i + 1][j] == ' '))
		return (1);
	return (0);
}

/**
 * @brief Loops every map row from 1 to n-1. For every '0' checks 
 * all surrounding tiles are '0' or '1' (no openings). 
 * For the spawn point does the same and 
 * stores its position.
 * @param map_rows Number of map rows
 * @param map Map structure
 * @return 0 on success, error code otherwise
 */
int	ft_check_rowsclosed(int map_rows, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (++i < map_rows - 1)
	{
		j = -1;
		while (map->map[i][++j])
		{
			if (map->map[i][j] == '0' || map->map[i][j] == map->spawn)
			{
				if (ft_tile_notclosed(map, i, j))
					return (ft_parse_error(ERROR_MAP_SURROUND));
			}
			if (map->map[i][j] == map->spawn)
			{
				map->spawn_y = i;
				map->spawn_x = j;
			}
		}
	}
	return (0);
}

/*
1) Check first row only contains 1s
2) Count rows and store number to check last row only contains 1s
3) Check all other rows
*/
int	ft_check_mapclosed(t_map *map)
{
	int	i;
	int	map_rows;

	i = 0;
	while (map->map[0][i])
	{
		if (map->map[0][i] != '1' && map->map[0][i] != ' ')
			return (ft_parse_error(ERROR_MAP_SURROUND));
		i++;
	}
	map_rows = 0;
	while (map->map[map_rows])
		map_rows++;
	i = 0;
	while (map->map[map_rows - 1][i])
	{
		if (map->map[map_rows - 1][i] != '1' && map->map[0][i] != ' ')
			return (ft_parse_error(ERROR_MAP_SURROUND));
		i++;
	}
	if (ft_check_rowsclosed(map_rows, map))
		return (1);
	return (0);
}

/*
1) Append map rows to map_str
2) Check for unexpcted chars in map and only one player spawn (N S W E)
3) Split map and store in struct, then check it's closed by walls 
	and fill the gaps
*/
int	ft_parse_map(char **line, int scenefd, t_map *map)
{
	char	*map_str;

	map_str = ft_strdup("");
	while (*line)
	{
		if (*line[0] == '\n')
			return (free(map_str), free(*line), ft_parse_error(ERROR_NL));
		map_str = ft_strjoin_free(map_str, *line);
		*line = get_next_line(scenefd);
	}
	if (ft_check_mapchars(map_str, map))
		return (free(map_str), 1);
	map->map = ft_split(map_str, '\n');
	free(map_str);
	if (!map->map)
		return (1);
	if (ft_check_mapclosed(map))
		return (1);
	return (0);
}
