
#include "cub3d.h"

int ft_wrong_file(char *scene)
{
    char    *ext;

    ext = ft_strrchr(scene, '.');
    if (ext && ext != scene && !ft_strxcmp(ext, ".cub"))
        return (0);
    return (1);
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
	


    return (0);
}