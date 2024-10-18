/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:12:58 by tparratt          #+#    #+#             */
/*   Updated: 2024/10/18 14:13:49 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*static void	print_all(t_map *map)
{
	int	i;

	ft_putendl_fd(map->no, 1);
	ft_putendl_fd(map->so, 1);
	ft_putendl_fd(map->ea, 1);
	ft_putendl_fd(map->we, 1);
	i = 0;
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
}*/

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
		ft_putendl_fd("Error\nIncorrect number of arguments", 2);
	else
	{
		parse(argv, &map);
		validate(&map);
	}
	setup_mlx(&map);
	free_map(&map);
	return (0);
}
