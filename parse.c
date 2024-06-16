#include "cub3d.h"

int	ft_wrong_file(char *scene)
{
	char	*ext;

	ext = ft_strrchr(scene, '.');
	if (ext && ext != scene && !ft_strxcmp(ext, ".cub"))
		return (0);
	return (1);
}

/*
1) Verify correct file type passed as argument
2) Open and start reading scene file
3) Call ft_parse_mapdata to get all necessary info
4) Call ft_parse_map to check map errors and store it in a 2D array
*/
int	ft_parse_input(int argc, char **argv, t_map *map)
{
	int 	scenefd;
	char	*line;
	
	if (argc != 2 || ft_wrong_file(argv[1]))
		return (ft_putstr_fd("Error\nWrong argument. Correct format is ./cub3d scene_file.cub\n", 2), 1);
	scenefd = open(argv[1], O_RDONLY);
	if (scenefd == -1)
		return (ft_putstr_fd("Error\nUnable to open specified scene file\n", 2), 1);
	ft_bzero(map, sizeof(t_map));
	line = get_next_line(scenefd);
	if (ft_parse_mapdata(&line, scenefd, map))
		return (ft_free_map(map), free(line), 1);
	if (ft_parse_map(&line, scenefd, map))
		return (ft_free_map(map), 1);
	
	int i = 0;
	int j = 0;
	map->size_x = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			j++;
			if (j > map->size_x)
				map->size_x = j;
		}
		i++;
	}
	map->size_y = i;








	return (0);
}
