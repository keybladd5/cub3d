
#include "cub3d.h"

int ft_wrong_file(char *scene)
{
    char    *ext;

    ext = ft_strrchr(scene, '.');
    if (ext && ext != scene && !ft_strxcmp(ext, ".cub"))
        return (0);
    return (1);
}

void    ft_load_mapdata(t_data *d, char *line)
{
    mlx_texture_t   *p_tex;

    while ((*line == ' ' || (*line >= 9 && *line <= 13)))
		line++;
    if (!ft_strncmp(line, "NO", 2))
        p_tex = d->no;
    else if (!ft_strncmp(line, "SO", 2))
        p_tex = d->so;
    else if (!ft_strncmp(line, "WE", 2))
        p_tex = d->we;
    else if (!ft_strncmp(line, "EA", 2))
        p_tex = d->ea;
    

}

int ft_parse_input(int argc, char **argv, t_data *d)
{
    (void)d;//tmp

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
	//GNL loop until all data has been found
    char    *line = get_next_line(scenefd);
    while (line && line[0] != '1' && line[0] != '0') //if a line begins with 0 or 1 means it's the map (always last element)
    {
        ft_load_mapdata(d, line);
        
        
    }




    return (0);
}