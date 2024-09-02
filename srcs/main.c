/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:12:58 by tparratt          #+#    #+#             */
/*   Updated: 2024/08/29 15:19:36 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void elements_to_null(t_map *map, int no_of_lines)
{
    int i;

    i = 0;
    map->no = NULL;
    map->so = NULL;
    map->ea = NULL;
    map->we = NULL;
    map->floor = NULL;
    map->ceiling = NULL;
    map->f = NULL;
    map->c = NULL;
    map->map = malloc((no_of_lines * sizeof(char *)) + 1);
    while (i < no_of_lines)
    {
        map->map[i] = NULL;
        i++;
    }
}

int main(int argc, char **argv)
{
    int     no_of_lines;
    t_map   map;
    
    if (argc == 2)
    {
        check_file_extension(argv[1]);
        no_of_lines = map_line_count(argv[1]);
        elements_to_null(&map, no_of_lines);
        set_initial_map(argv[1], &map);
        set_final(&map);
        
        validate(&map);

        //ft_putendl_fd(map.no, 1);
        //ft_putendl_fd(map.so, 1);
        //ft_putendl_fd(map.ea, 1);
        //ft_putendl_fd(map.we, 1);
        //print_2d(map.map);
        
        free_map(&map);
    }
    else
        ft_putendl_fd("Error\nIncorrect number of arguments", 2);
    return (0);
}

/*
Parses the file into a struct containing:
    - A 2d character array containing the map
    - Strings for each north, south, east and west texture
    - A copy of the map for use in validation
    - Strings for floor and ceiling for use in validation
    - Integer arrays for floor and ceiling RGB colors

Handles the following errors:
    - Incorrect number of arguments
    - RGB contains too many integers
    - RGB contains alphabets
    - RGB integer not in correct range
    - Not all elements present
    - Elements must appear before map content
    - Cannot open file
    - Empty file
    - Wrong file extension
    - Invalid map character(s)
    - More than one start position
    - No start position
    - Empty line within map
    - Map not surrounded by walls
    - Start position surrounded by walls

Still to do: (This list will get bigger before it gets smaller!)
    - Handle very large maps
    - Texture file error handling?
    - Handle freeing at exit
    - Malloc error handling
    - File opening error handling
    - Handle ' ' character inside map?
    - Norminette
*/
