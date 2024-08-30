#include "../includes/cub3d.h"

static size_t	valid_position(t_map *map, size_t i, size_t j)
{
    if (!map->copy[i])
        return (0);
    else if (!map->copy[i][j])
        return (0);
	else if (map->copy[i][j] == '1')
		return (0);
    else if (map->copy[i][j] == 'a')
		return (0);
	return (1);
}

static void	fill_if_valid(t_map *map, int i, int j)
{
    if (i < 0 || j < 0)
        return ;
	else if (!valid_position(map, i, j))
		return ;
	map->copy[i][j] = 'a';
	fill_if_valid(map, i - 1, j);
	fill_if_valid(map, i + 1, j);
	fill_if_valid(map, i, j - 1);
	fill_if_valid(map, i, j + 1);
}

static void compare_maps(t_map *map)
{
    int i;
    int j;

    i = 0;
    while (map->map[i])
    {
        j = 0;
        while (map->map[i][j])
        {
            if (map->map[i][j] == ' ' && map->copy[i][j] == 'a')
            {
                free_2d(map->copy);
                print_error("Map not surrounded by walls");
            }
            j++;
        }
        i++;
    }
}

static void copy_map(t_map *map)
{
    int len;
    int i;

    len = 0;
    len = len_2d(map->map);
    map->copy = malloc(len * sizeof(char *) + 1);
    i = 0;
    while (map->map[i])
    {
        map->copy[i] = ft_strdup(map->map[i]);
        i++;
    }
    map->copy[i] = NULL;
}

void	check_walls(t_map *map)
{
	int     i;
    int 	j;
    int     flag;

    i = 0;
    flag = 0;
    while (map->map[i])
    {
        j = 0;
        while (map->map[i][j])
        {
            if (map->map[i][j] == 'N' || map->map[i][j] == 'S' || map->map[i][j] == 'E' || map->map[i][j] == 'W')
            {
                flag = 1;
                break ;
            }
            j++;
        }
        if (flag == 1)
            break ;
        i++;
    }
    copy_map(map);
	fill_if_valid(map, i, j);
    compare_maps(map);
    free_2d(map->copy);
}
