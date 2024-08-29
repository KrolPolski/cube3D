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

int main(int argc, char **argv)
{
    int     no_of_lines;
    t_map   map;
    
    if (argc == 2)
    {
        check_file_extension(argv[1]);
        no_of_lines = map_line_count(argv[1]);
        set_initial_map(argv[1], no_of_lines, &map);
        set_final(&map);
        
        validate(&map);

        ft_putendl_fd(map.no, 1);
        ft_putendl_fd(map.so, 1);
        ft_putendl_fd(map.ea, 1);
        ft_putendl_fd(map.we, 1);
        print_2d(map.map);
        
        free_map(&map);
    }
    else
        ft_putendl_fd("Error\nIncorrect number of arguments", 2);
    return (0);
}
