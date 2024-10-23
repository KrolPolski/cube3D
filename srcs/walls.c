/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 09:51:01 by tparratt          #+#    #+#             */
/*   Updated: 2024/10/23 17:00:25 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* checks that we are within the map, character is not  wall,
and hasn't been already filled */
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

/* recursively fills the space within the map with 'a' characters */
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

/* checks that there are no gaps in the walls by comparing the maps */
static void	compare_maps(t_map *map)
{
	print_2d(map->copy);
	size_t	i;
	size_t	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == ' ' && map->copy[i][j] == 'a')
			{
				free_2d(map->copy);
				print_error("Map not surrounded by walls", map);
			}
			if ((i == len_2d(map->map) || i == 0 || j == (ft_strlen(map->map[i])
						- 1) || j == 0) && map->copy[i][j] == 'a')
			{
				free_2d(map->copy);
				print_error("Map not surrounded by walls", map);
			}
			j++;
		}
		i++;
	}
}

/* sets the flood fill start position */
static int	get_start_pos(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->copy[i])
	{
		j = 0;
		while (map->copy[i][j])
		{
			if (map->copy[i][j] == '0')
			{
				map->start_i = i;
				map->start_j = j;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

/*gets the start position for fill_if_valid, 
copies map, fills if valid, compares maps
until there are no more 0s in the map */
void	check_walls(t_map *map)
{
	copy_map(map);
	while (get_start_pos(map))
	{
		get_start_pos(map);
		fill_if_valid(map, map->start_i, map->start_j);
		compare_maps(map);
	}
	free_2d(map->copy);
}
