/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:13:27 by tparratt          #+#    #+#             */
/*   Updated: 2024/08/29 16:54:31 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void  check_file_extension(char *arg)
{
    char    *ext;
    
    ext = ft_strchr(arg, '.');
    if (ext == NULL || ft_strncmp(ext, ".cub", 5))
        print_error("Wrong file extension");
}

static int  all_remaining(int i, char **arr)
{
    while (arr[i])
    {
        if (!all_whitespace(arr[i]))
            return (0);
        i++;
    }
    return (1);
}

// static int  check_inlets(char **map, size_t i, size_t j)
// {
//     int res;

//     res = 0;
//     if (i != 0 && i != len_2d(map) && j != 0 && j != ft_strlen(map[i]) - 1)
//     {
//         if (map[i - 1][j] != '1' && map[i - 1][j] != ' ') // what if the character is on the wall and a different char?
//             res = 1;
//         if (map[i + 1][j] != '1' && map[i + 1][j] != ' ')
//             res = 2;
//         if (map[i][j - 1] != '1' && map[i][j - 1] != ' ')
//             res = 3;
//         if (map[i][j + 1] != '1' && map[i][j + 1] != ' ')
//             res = 4;
//     }
//     else if (i == 0 && j != 0 && j != ft_strlen(map[i]) - 1)
//     {
//         if (map[i + 1][j] != '1' && map[i + 1][j] != ' ')
//             res = 5;
//         if (map[i][j - 1] != '1' && map[i][j - 1] != ' ')
//             res = 6;
//         if (map[i][j + 1] != '1' && map[i][j + 1] != ' ')
//             res = 7;
//     }
//     else if (i == len_2d(map) && j != 0 && j != ft_strlen(map[i]) - 1)
//     {
//         if (map[i - 1][j] != '1' && map[i - 1][j] != ' ')
//             res = 8;
//         if (map[i][j - 1] != '1' && map[i][j - 1] != ' ')
//             res = 9;
//         if (map[i][j + 1] != '1' && map[i][j + 1] != ' ')
//             res = 10; 
//     }
//     else if (j == 0 && i != 0 && i != len_2d(map))
//     {
//         if (map[i - 1][j] != '1' && map[i - 1][j] != ' ')
//             res = 11;
//         if (map[i + 1][j] != '1' && map[i + 1][j] != ' ')
//             res = 12;
//         if (map[i][j + 1] != '1' && map[i][j + 1] != ' ')
//             res = 13;
//     }
//     else if (j != ft_strlen(map[i]) - 1 && i != 0 && i != len_2d(map))
//     {
//         if (map[i - 1][j] != '1' && map[i - 1][j] != ' ')
//             res = 14;
//         if (map[i + 1][j] != '1' && map[i + 1][j] != ' ')
//             res = 15;
//         if (map[i][j - 1] != '1' && map[i][j - 1] != ' ')
//             res = 16;
//     }
//     if (res > 0)
//         print_error("Map not surrounded by walls");
//     return (res);
// }

// static void check_walls(t_map *map)
// {
//     size_t i;
//     size_t len;
//     size_t j;
    
//     i = 0;
//     len = len_2d(map->map);
//     j = 0;
//     while (map->map[i][j]) // first char in column
//     {
//         i = 0;
//         while (map->map[i][j] == ' ')
//         {
//             check_inlets(map->map, i, j);
//             i++;
//         }
//         if (map->map[i][j] != '1')
//             print_error("Map not surrounded by walls");
//         j++;
//     }
//     j = 0;
//     while (map->map[i][j]) // last char in column
//     {
//         i = len_2d(map->map);
//         while (map->map[i][j] == ' ')
//         {
//             check_inlets(map->map, i, j);
//             i--;
//         }
//         if (map->map[i][j] != '1')
//             print_error("Map not surrounded by walls");
//         j++;
//     }
//     i = 0;
//     while (map->map[i][j]) // first char in row
//     {
//         j = 0;
//         while (map->map[i][j] == ' ')
//         {
//             check_inlets(map->map, i , j);
//             j++;
//         }
//         if (map->map[i][j] != '1')
//             print_error("Map not surrounded by walls");
//         i++;
//     }
//     i = 0;
//     while (map->map[i][j]) // last char in row
//     {
//         j = ft_strlen(map->map[i]) - 1;
//         while (map->map[i][j] == ' ')
//         {
//             check_inlets(map->map, i, j);
//             j--;
//         }
//         if (map->map[i][j] != '1')
//             print_error("Map not surrounded by walls");
//         i++;
//     }
// }

static size_t	valid_position(t_map *map, size_t i, size_t j)
{
    if (!map->map[i])
        return (0);
    else if (!map->map[i][j])
        return (0);
	else if (map->map[i][j] == '1')
		return (0);
	else if (map->map[i][j] == 1)
		return (0);
	return (1);
}

static void	fill_if_valid(t_map *map, size_t i, size_t j)
{
	if (!valid_position(map, i, j))
		return ;
	map->map[i][j] = 1;
	fill_if_valid(map, i - 1, j);
	fill_if_valid(map, i + 1, j);
	fill_if_valid(map, i, j - 1);
	fill_if_valid(map, i, j + 1);
}

static void	valid_path(t_map *map)
{
	size_t	i;
	size_t	j;

	fill_if_valid(map, 0, 0);
	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] != '1' && map->map[i][j] != 1)
                print_error("Map not surrounded by walls");
			j++;
		}
		i++;
	}
}

static void valid_chars(char c)
{
    if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != ' ')
        print_error("Invalid map character(s)");
}

static int start_positions(char c, int player_count)
{
    if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
    {
        player_count++;
        if (player_count > 1)
            print_error("More than one start position");
    }
    return (player_count);
}

static void check_chars(t_map *map)
{
    int i;
    int j;
    int player_count;
    int empty_space_count;

    i = 0;
    player_count = 0;
    empty_space_count = 0;
    while (map->map[i])
    {
        j = 0;
        while (map->map[i][j])
        {
            if (map->map[i][j] == '0')
                empty_space_count++;
            player_count = start_positions(map->map[i][j], player_count);
            valid_chars(map->map[i][j]);
            j++;
        }
        i++;
    }
    if (player_count == 0)
        print_error("No start position");
    if (empty_space_count == 0)
        print_error("No empty space");
}

static void find_empty_line(t_map *map)
{
    int i;

    i = 0;
    while (map->map[i])
    {
        if (all_whitespace(map->map[i]) && !all_remaining(i, map->map))
            print_error("Empty line within map");
        i++;
    }
}

void    validate(t_map *map)
{
    find_empty_line(map);
    check_chars(map);
    valid_path(map); // need to create the whitespace around the outside of the array
    //check_walls(map);
}