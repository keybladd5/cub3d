#include "cub3d.h"

int	ft_wrong_file(char *scene)
{
	char	*ext;

	ext = ft_strrchr(scene, '.');
	if (ext && ext != scene && !ft_strxcmp(ext, ".cub"))
		return (0);
	return (1);
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
	int	data_count = 0;
	char    *line = get_next_line(scenefd);
	while (line && data_count < 6 && line[0] != '1' && line[0] != '0') //if a line begins with 0 or 1 means it's the map (always last element)
	{
		if (line[0] != '\n')
		{
			if (ft_load_mapdata(map, line))
				return (ft_free_map(map), free(line), 1);
			data_count++;
		}
		free(line);
		line = get_next_line(scenefd);
	}
	//Verify all necessary data was found
	if (!map->no || !map->so || !map->we || !map->ea || !map->f_color || !map->c_color)
		return (ft_putstr_fd("Error\nMissing texture/background data\n", 2), free(line), ft_free_map(map), 1);
	//GNL loop to read map
	//skip empty lines
	while(line && (line[0] == '\n'))
	{
		free(line);
		line = get_next_line(scenefd);
	}
	
	//append map rows to map_str
	char	*map_str = ft_strdup("");
	while(line)
	{
		if (line[0] == '\n')
			return (ft_putstr_fd("Error\nEmpty line found in map\n", 2), free(map_str), free(line), ft_free_map(map), 1);
		map_str = ft_strjoin_free(map_str, line);
		line = get_next_line(scenefd);
	}
	//check for unexpcted chars in map and only one player spawn (N S W E)
	int i = 0;
	int spawn = 0;
	while (map_str[i])
	{
		if (map_str[i] == 'N' || map_str[i] == 'S' || map_str[i] == 'W' || map_str[i] == 'E')
		{
			if (spawn)
				return (ft_putstr_fd("Error\nMultiple spawn points found in map\n", 2), free(map_str), ft_free_map(map), 1);
			else
				spawn = 1;
		}
		else if (map_str[i] != '1' && map_str[i] != '0' && map_str[i] != ' ' && map_str[i] != '\n')
			return (ft_putstr_fd("Error\nUnexpected character found in map\n", 2), free(map_str), ft_free_map(map), 1);
		i++;
	}
	if (!spawn)
		return (ft_putstr_fd("Error\nNo player spawn point found in map\n", 2), free(map_str), ft_free_map(map), 1);
	//split map and store in struct, then check it's closed by walls and fill the gaps
	map->map = ft_split(map_str, '\n');
	if (!map->map)
		return (free(map_str), 1);
	free(map_str);
	
	//check first row only contains 1s
	
	
	//count rows and store number to check last row only contains 1s
	int map_rows = 0;
	while (map->map[map_rows])
		map_rows++;
	
	//get longest row length and store the value. Any row shorter than that must be expanded to that length, filling it with 1s




	
	//debug
	int	k = 0;
	while (map->map[k])
	{
		printf("%s\n", map->map[k]);
		k++;
	}

	return (0);
}
