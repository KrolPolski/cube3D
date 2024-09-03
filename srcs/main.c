/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:12:58 by tparratt          #+#    #+#             */
/*   Updated: 2024/09/03 11:06:24 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main(int argc, char **argv)
{
    t_map   map;
    
    if (argc != 2)
        ft_putendl_fd("Error\nIncorrect number of arguments", 2);
    else
    {
        parse(argv, &map);
        validate(&map);

        //ft_putendl_fd(map.no, 1);
        //ft_putendl_fd(map.so, 1);
        //ft_putendl_fd(map.ea, 1);
        //ft_putendl_fd(map.we, 1);
        
        print_2d(map.map);
        free_map(&map);
    }
	// setup_mlx(&map);
    // free_map(&map);
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
    - Malloc failure in gnl??
    - Norminette
*/
