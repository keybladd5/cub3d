
#include "cub3d.h"

int ft_wrong_file(char *scene)
{
    char    *ext;

    ext = ft_strrchr(scene, '.');
    if (ext && ext != scene && !ft_strxcmp(ext, ".cub"))
        return (0);
    return (1);
}

int	ft_load_texture(t_data *d, char *line)
{
	mlx_texture_t   **p_tex;

	if (!ft_strncmp(line, "NO", 2))
		p_tex = d->no;
    else if (!ft_strncmp(line, "SO", 2))
        p_tex = d->so;
    else if (!ft_strncmp(line, "WE", 2))
        p_tex = d->we;
    else if (!ft_strncmp(line, "EA", 2))
		p_tex = d->ea;
	line += 2;
	while (ft_isspace(*line) && *line != '\n')
		line++;
	line[ft_strlen(line) - 1] = '\0';
	*p_tex = mlx_load_png(line);
	if (!*p_tex) //la funcion mlx_load_png ya printea un mensaje de error cuando falla (?)
	{
		printf("Error\nUnable to open texture asset\n");
		return (1);
	}
	return (0);
}

void	ft_load_bg(t_data *d, char *line)
{
	int	*p_color;
	char	**rgb;
  
    if (!ft_strncmp(line, "F", 1))
		p_color = d->f_color;
    else if (!ft_strncmp(line, "C", 1))
		p_color = d->c_color;
	line++;
	while (ft_isspace(*line) && *line != '\n')
		line++;
	line[ft_strlen(line) - 1] = '\0';
	rgb = ft_split(line, ',');
	*p_color = get_rgba(ft_atoi(rgb[0]), ft_atoi(rgb[1]), ft_atoi(rgb[2]), 255);
	free(rgb[0]);
	free(rgb[1]);
	free(rgb[2]);
	free(rgb);
}

int    ft_load_mapdata(t_data *d, char *line)
{
	while (ft_isspace(*line) && *line != '\n')
		line++;
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2) || !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2))
	{
		if(ft_load_texture(d, line))
			return (1);
	}
	else if (!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
		ft_load_bg(d, line);
	return (0);
}

int ft_parse_input(int argc, char **argv, t_data *d)
{
	//Verify correct file type passed as argument
    if (argc != 2 || ft_wrong_file(argv[1]))
    {
        printf("Error\nWrong argument. Correct format is ./cub3d scene_file.cub\n");
        return (1);
    }

	//Open and start reading scene file
    int scenefd = open(argv[1], O_RDONLY);
    if (scenefd == -1)
	{
		printf("Error\nUnable to open specified scene file\n");
		return (1);
	}
	//init textures & background data
	d->no = ft_calloc(1, sizeof(mlx_texture_t));
	d->so = ft_calloc(1, sizeof(mlx_texture_t));
	d->we = ft_calloc(1, sizeof(mlx_texture_t));
	d->ea = ft_calloc(1, sizeof(mlx_texture_t));
	d->f_color = ft_calloc(1, sizeof(int));
	d->c_color = ft_calloc(1, sizeof(int));
	//GNL loop until all data has been found
    char    *line = get_next_line(scenefd);
    while (line && line[0] != '1' && line[0] != '0') //if a line begins with 0 or 1 means it's the map (always last element)
    {
        if (line[0] != '\n')
			if(ft_load_mapdata(d, line))
				return (free(line), 1);
        free(line);
		line = get_next_line(scenefd);
    }

	return (0);
}