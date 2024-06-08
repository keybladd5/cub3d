
#include "cub3d.h"

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void    ft_free_map(t_map *map)
{
	if (map->no)
		mlx_delete_texture(map->no);
	if (map->so)
		mlx_delete_texture(map->so);
	if (map->we)
		mlx_delete_texture(map->we);
	if (map->ea)
		mlx_delete_texture(map->ea);
}

void	ft_search_replace(char *str, char og, char new)
{
	int	len;

	len = ft_strlen(str);
	while (--len)
	{
		if (str[len] == og)
			str[len] = new;
	}
}