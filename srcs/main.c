/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:42:37 by tparratt          #+#    #+#             */
/*   Updated: 2024/08/29 15:20:00 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main(int argc, char **argv)
{
    int     no_of_lines;
    t_map   map;
    
    if (argc == 2)
    {
        if (check_file_extension(argv[1]))
            return (1);
        no_of_lines = map_line_count(argv[1]);
        set_initial_map(argv[1], no_of_lines, &map);
        set_final(&map);
        
        //print_2d(map.map);
        
        //free(map.c);
        //free(map.f);
        //free(map.no);
        //free(map.so);
        //free(map.ea);
        //free(map.we);
        //free_2d(map.map);
    }
    else
        ft_putendl_fd("Incorrect number of arguments", 2);
	/*int i = 0;
	while (map.map[i])

		{ft_printf("%s\n", map.map[i]);
		i++;}*/
	setup_mlx(&map);
    return (0);
}
