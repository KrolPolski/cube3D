/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:12:58 by tparratt          #+#    #+#             */
/*   Updated: 2024/09/05 13:32:25 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void print_all(t_map *map)
{
    ft_putendl_fd(map->no, 1);
    ft_putendl_fd(map->so, 1);
    ft_putendl_fd(map->ea, 1);
    ft_putendl_fd(map->we, 1);
    int i = 0;
    while (i < 3)
    {
        ft_printf("%d ", map->f[i]);
        i++;
    }
    ft_printf("\n");
    i = 0;
    while (i < 3)
    {
        ft_printf("%d ", map->c[i]);
        i++;
    }
    ft_printf("\n");
    print_2d(map->map);
}

int main(int argc, char **argv)
{
    t_map   map;
    
    if (argc != 2)
        ft_putendl_fd("Error\nIncorrect number of arguments", 2);
    else
    {
        parse(argv, &map);
        validate(&map);
        
        //print_all(&map);
        //free_map(&map);
    }
	setup_mlx(&map);
    free_map(&map);
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

Now also have:
    - texture path validation (must have .png extension, must exist/have correct path, must have correct permissions)
    - cleanup in case of exit
    - memory allocation error handling
*/
