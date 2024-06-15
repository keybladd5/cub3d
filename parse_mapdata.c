#include "cub3d.h"

mlx_texture_t	*ft_load_texture(char *line)
{
	mlx_texture_t	*p_tex;

	line += 2;
	while (ft_isspace(*line) && *line != '\n') //if identifier not followed by at least 1 space = Error???
		line++;
	ft_search_replace(line, '\n', '\0');
	p_tex = mlx_load_png(line);
	if (!p_tex) //la funcion mlx_load_png ya printea un mensaje de error cuando falla (?)
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
	if (!ft_isdigit(line[0]) || !ft_isdigit(line[ft_strlen(line) - 1]) || commas != 2)
		return (1);
	return (0);
}

// load background colors
int	ft_load_bg(t_map *map, char *line)
{
	char	**rgb;
	int		i;
	int		rgb_arr[3];
	char	c_or_f;

	c_or_f = *line++;
	while (ft_isspace(*line) && *line != '\n') //if identifier not followed by at least 1 space = Error???
		line++;
	ft_search_replace(line, '\n', '\0');
	if (ft_check_rgb(line))
		return (1);//Error msg
	rgb = ft_split(line, ',');
	if (!rgb)
		return (1);//Error msg
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
	while (ft_isspace(*line) && *line != '\n')
		line++;
	if (ft_check_dupdata(map, line))
		return (ft_putstr_fd("Error\nDuplicate scene data found\n", 2), 1);
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2) || !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2))
	{
		if (ft_read_texture(map, line))
			return (1);
	}
	else if (!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
	{
		if (ft_load_bg(map, line))
			return (ft_putstr_fd("Error\nWrong Floor/Ceiling color format. Must be R,G,B in range [0,255]\n", 2), 1);
	}
	else
		return (ft_putstr_fd("Error\nUnexpeced data found in scene file\n", 2), 1);
	return (0);
}
