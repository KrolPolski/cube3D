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

static int	fill_if_valid(t_map *map, int i, int j)
{
    static int fills;

    if (i < 0 || j < 0)
        return (fills);
	else if (!valid_position(map, i, j))
		return (fills);
    fills++;
	map->copy[i][j] = 'a';
	fills = fill_if_valid(map, i - 1, j);
	fills = fill_if_valid(map, i + 1, j);
	fills = fill_if_valid(map, i, j - 1);
	fills = fill_if_valid(map, i, j + 1);
    return (fills);
}

static void compare_maps(t_map *map)
{
    size_t i;
    size_t j;

    i = 0;
    while (map->map[i])
    {
        j = 0;
        while (map->map[i][j])
        {
            if (map->map[i][j] == ' ' && map->copy[i][j] == 'a')
            {
                free_2d(map->copy);
                free_map(map);
                print_error("Map not surrounded by walls");
            }
            if ((i == len_2d(map->map) || i == 0 || j == (ft_strlen(map->map[i]) - 1) || j == 0) && map->copy[i][j] == 'a')
            {
                free_2d(map->copy);
                free_map(map);
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
    if (!map->copy)
    {
        free_map(map);
        print_error("Memory allocation failure");
    }
    i = 0;
    while (map->map[i])
    {
        map->copy[i] = ft_strdup(map->map[i]);
        if (!map->copy[i])
        {
            free_map(map);
            print_error("Memory allocation failure");
        }
        i++;
    }
    map->copy[i] = NULL;
}

void	check_walls(t_map *map)
{
	int     i;
    int 	j;
    int     flag;
    int     fills;

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
	fills = fill_if_valid(map, i, j);
    if (fills == 1)
    {
        free_2d(map->copy);
        free_map(map);
        print_error("Start position surrounded by walls");
    }
    compare_maps(map);
    free_2d(map->copy);
}
