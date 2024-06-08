#include "cub3d.h"

int	ft_wrong_file(char *scene)
{
	char	*ext;

	ext = ft_strrchr(scene, '.');
	if (ext && ext != scene && !ft_strxcmp(ext, ".cub"))
		return (0);
	return (1);
}

mlx_texture_t	*ft_load_texture(char *line)
{
	mlx_texture_t	*p_tex;

	line += 2;
	while (ft_isspace(*line) && *line != '\n')
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
		map->no = ft_load_texture(line);
		if (!map->no)
			return (1);
	}
	else if (!ft_strncmp(line, "SO", 2))
	{
		map->so = ft_load_texture(line);
		if (!map->so)
			return (1);
	}
	else if (!ft_strncmp(line, "WE", 2))
	{
		map->we = ft_load_texture(line);
		if (!map->we)
			return (1);
	}
	else if (!ft_strncmp(line, "EA", 2))
	{
		map->ea = ft_load_texture(line);
		if (!map->ea)
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
	while (ft_isspace(*line) && *line != '\n')
		line++;
	ft_search_replace(line, '\n', '\0');
	if (ft_check_rgb(line))
		return (1);
	rgb = ft_split(line, ',');
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

int	ft_load_mapdata(t_map *map, char *line)
{
	while (ft_isspace(*line) && *line != '\n')
		line++;
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

int	ft_parse_input(int argc, char **argv, t_map *map)
{
	ft_bzero(map, sizeof(t_map));
	//Verify correct file type passed as argument
	if (argc != 2 || ft_wrong_file(argv[1]))
		return (ft_putstr_fd("Error\nWrong argument. Correct format is ./cub3d scene_file.cub\n", 2), 1);
	//Open and start reading scene file
	int scenefd = open(argv[1], O_RDONLY);
	if (scenefd == -1)
		return (ft_putstr_fd("Error\nUnable to open specified scene file\n", 2), 1);
	//GNL loop until all data has been found
	char    *line = get_next_line(scenefd);
	while (line && line[0] != '1' && line[0] != '0') //if a line begins with 0 or 1 means it's the map (always last element)
	{
		if (line[0] != '\n')
			if (ft_load_mapdata(map, line))
				return (ft_free_map(map), free(line), 1);
		free(line);
		line = get_next_line(scenefd);
	}
	//Verify all necessary data was found
	if (!map->no || !map->so || !map->we || !map->ea || !map->f_color || !map->c_color)
		return (ft_putstr_fd("Error\nMissing texture/background data\n", 2), free(line), ft_free_map(map), 1);
	return (0);
}
