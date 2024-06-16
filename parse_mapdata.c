/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mapdata.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polmarti <polmarti@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:36:11 by polmarti          #+#    #+#             */
/*   Updated: 2024/06/16 18:36:16 by polmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_check_rgb(char *line)
{
	int	i;
	int	commas;

	i = -1;
	commas = 0;
	while (line[++i])
	{
		if (!ft_isdigit(line[i]))
		{
			if (line[i] == ',' && ft_isdigit(line[i + 1]))
				commas++;
			else
				return (1);
		}
	}
	if (!ft_isdigit(line[0]) || !ft_isdigit(line[ft_strlen(line) - 1]) \
	|| commas != 2)
		return (1);
	return (0);
}

// load background colors
int	ft_load_bg(t_map *map, char *line, char c_or_f)
{
	char	**rgb;
	int		i;
	int		rgb_arr[3];

	ft_search_replace(line, '\n', '\0');
	if (ft_check_rgb(line))
		return (1);
	rgb = ft_split(line, ',');
	if (!rgb)
		return (1);
	i = 0;
	while (i < 3)
	{
		rgb_arr[i] = ft_atoi(rgb[i]);
		if (rgb_arr[i] < 0 || rgb_arr[i] > 255)
			return (free(rgb[0]), free(rgb[1]), free(rgb[2]), free(rgb), 1);
		i++;
	}
	if (c_or_f == 'F')
		map->f_color = get_rgba(rgb_arr[0], rgb_arr[1], rgb_arr[2], 255);
	else if (c_or_f == 'C')
		map->c_color = get_rgba(rgb_arr[0], rgb_arr[1], rgb_arr[2], 255);
	return (free(rgb[0]), free(rgb[1]), free(rgb[2]), free(rgb), 0);
}

int	ft_check_dupdata(t_map *map, char *line)
{
	if ((!ft_strncmp(line, "NO", 2) && map->tex.no) || \
	(!ft_strncmp(line, "SO", 2) && map->tex.so) || \
	(!ft_strncmp(line, "WE", 2) && map->tex.we) || \
	(!ft_strncmp(line, "EA", 2) && map->tex.ea) || \
	(!ft_strncmp(line, "F", 1) && map->f_color) || \
	(!ft_strncmp(line, "C", 1) && map->c_color))
		return (1);
	return (0);
}

int	ft_load_mapdata(t_map *map, char *line)
{
	char	c_or_f;

	line = ft_skip_spaces(line);
	if (ft_check_dupdata(map, line))
		return (ft_parse_error(ERROR_DUP_DATA));
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2) \
	|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2))
	{
		if (ft_read_texture(map, line))
			return (1);
	}
	else if (!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
	{
		c_or_f = *line;
		if (ft_load_bg(map, ft_skip_spaces(++line), c_or_f))
			return (ft_parse_error(ERROR_RGBA));
	}
	else
		return (ft_parse_error(ERROR_DATA));
	return (0);
}

// GNL loop until all data has been found or start of the map, 
//then verify all data is present and skip empty lines
int	ft_parse_mapdata(char **line, int scenefd, t_map *map)
{
	int		data_count;

	data_count = 0;
	while (*line && data_count < 6 && *line[0] != '1' && *line[0] != '0')
	{
		if (*line[0] != '\n')
		{
			if (ft_load_mapdata(map, *line))
				return (1);
			data_count++;
		}
		free(*line);
		*line = get_next_line(scenefd);
	}
	if (!map->tex.no || !map->tex.so || !map->tex.we || \
	!map->tex.ea || !map->f_color || !map->c_color)
		return (ft_parse_error(ERROR_TEX_BG));
	while (*line && (*line[0] == '\n'))
	{
		free(*line);
		*line = get_next_line(scenefd);
	}
	return (0);
}
