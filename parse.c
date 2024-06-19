/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-tole <ade-tole@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 20:02:57 by ade-tole          #+#    #+#             */
/*   Updated: 2024/06/16 20:02:59 by ade-tole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
@brief Prints error message based on error type and returns 1.
 *
 * This function prints a specific error message to standard error (fd 2)
 * depending on the provided error type (`type`). It then returns 1 to indicate
 * an error condition.
 * @param type Error type code.
 *
 * @return Always returns 1 (error condition).
 */
int	ft_parse_error(int type)
{
	ft_putstr_fd("Error\n", 2);
	if (type == ERROR_ARG)
		ft_putstr_fd("Wrong argument. Format should be ./cub3d file.cub\n", 2);
	else if (type == ERROR_OPEN)
		ft_putstr_fd("Unable to open specified scene file\n", 2);
	else if (type == ERROR_TEX_BG)
		ft_putstr_fd("Missing texture/background data\n", 2);
	else if (type == ERROR_NL)
		ft_putstr_fd("Empty line found in map\n", 2);
	else if (type == ERROR_CHAR)
		ft_putstr_fd("Unexpected character found in map\n", 2);
	else if (type == ERROR_SPAWN)
		ft_putstr_fd("Multiple spawn points found in map\n", 2);
	else if (type == ERROR_NO_SPAWN)
		ft_putstr_fd("No player spawn point found in map\n", 2);
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

/**
 * @brief Checks for valid scene file extension (.cub).
 * @param scene Path to the scene file.
 * @return 0 if valid (.cub), 1 otherwise.
 */
int	ft_wrong_file(char *scene)
{
	char	*ext;

	ext = ft_strrchr(scene, '.');
	if (ext && ext != scene && !ft_strxcmp(ext, ".cub"))
		return (0);
	return (1);
}

/**
 * @brief Initializes map size and minimap tile size.
 *
 * This function calculates the dimensions (width and height) of the map by
 * iterating through the map data (`d->map.map`) and updates the `size_x` and
 * `size_y` members of the `d->map` structure. 
 *
 * It then determines the appropriate tile size for the minimap based on 
 * the map size and available screen space (25% of each dimension).
 * The minimap tile size is chosen as the smaller value relative to 
 * screen dimensions to ensure the entire map fits within the minimap area.
 *
 * @param d Pointer to the data structure (`t_data`).
 */
void	init_data_map(t_data *d)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	d->map.size_x = 0;
	while (d->map.map[i])
	{
		j = 0;
		while (d->map.map[i][j])
		{
			j++;
			if (j > d->map.size_x)
				d->map.size_x = j;
		}
		i++;
	}
	d->map.size_y = i;
	if ((WIDTH * 0.25 / d->map.size_x) < (HEIGHT * 0.25 / d->map.size_y))
		d->minimap.tile_size = WIDTH * 0.25 / d->map.size_x;
	else
		d->minimap.tile_size = HEIGHT * 0.25 / d->map.size_y;
}

/**
 * @brief Initializes player data with movement, direction,
 * position, FOV, flags.
 *
 * @param d Pointer to the data structure.
 */
void	init_data_player(t_data *d)
{
	d->data_player.advance = 0;
	d->data_player.turn_on = 0;
	if (d->map.spawn == 'E')
		d->data_player.angle_rotation = 0.0;
	else if (d->map.spawn == 'S')
		d->data_player.angle_rotation = M_PI / 2;
	else if (d->map.spawn == 'W')
		d->data_player.angle_rotation = M_PI;
	else if (d->map.spawn == 'N')
		d->data_player.angle_rotation = 3 * M_PI / 2;
	d->data_player.speed_advance = 4.0;
	d->data_player.speed_turn_on = 3.5 * (M_PI / 180.0);
	d->data_player.x = d->map.spawn_x * TILE_SIZE + (TILE_SIZE >> 1);
	d->data_player.y = d->map.spawn_y * TILE_SIZE + (TILE_SIZE >> 1);
	d->data_player.fov_radians = (FOV * M_PI) / 180;
	d->data_player.lateral_move = 0;
	d->data_player.west = false;
	d->data_player.south = false;
}

/**
 * @brief Parses scene file and populates map data.
 *
 * This function performs the following tasks:
 *  1. Validates file argument (correct number and type).
 *  2. Opens scene file for reading.
 *  3. Calls `ft_parse_mapdata` to extract map information.
 *  4. Calls `ft_parse_map` to validate map data and store it.
 *  5. Cleans up resources on error or success.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @param map Pointer to the map structure to be populated.
 * @return 0 on success, 1 on error (parsing or memory allocation).
 */
int	ft_parse_input(int argc, char **argv, t_map *map)
{
	int		scenefd;
	char	*line;

	if (argc != 2 || ft_wrong_file(argv[1]))
		return (ft_parse_error(ERROR_ARG));
	scenefd = open(argv[1], O_RDONLY);
	if (scenefd == -1)
		return (ft_parse_error(ERROR_OPEN));
	ft_bzero(map, sizeof(t_map));
	line = get_next_line(scenefd);
	if (ft_parse_mapdata(&line, scenefd, map))
		return (ft_free_map(map), free(line), 1);
	if (ft_parse_map(&line, scenefd, map))
		return (ft_free_map(map), 1);
	return (0);
}
