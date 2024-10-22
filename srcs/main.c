/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:12:58 by tparratt          #+#    #+#             */
/*   Updated: 2024/10/22 11:54:31 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
	{
		ft_putendl_fd("Error\nIncorrect number of arguments", 2);
		return (1);
	}
	parse(argv, &map);
	validate(&map);
	setup_mlx(&map);
	free_map(&map);
	return (0);
}
