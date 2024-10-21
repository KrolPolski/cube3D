/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_plyr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:27:40 by rboudwin          #+#    #+#             */
/*   Updated: 2024/10/21 17:23:47 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Prints error message and exits if we can't find a starting position 
for the player */
void	check_found(int found)
{
	if (!found)
	{
		ft_putstr_fd("Error: No starting position found\n", 2);
		exit(1);
	}
}

/* Locates starting position for the player */
void	find_start_position(t_map *map, int *x, int *y)
{
	int	found;

	found = 0;
	*y = 0;
	*x = 0;
	while (map->map[*y])
	{
		while (map->map[*y][*x])
		{
			if (ft_strchr("NESW", map->map[*y][*x]))
			{
				found = 1;
				break ;
			}
			(*x)++;
		}
		if (!found)
		{
			*x = 0;
			(*y)++;
		}
		else
			break ;
	}
	check_found(found);
}

/* Determines initial player location and orientation */
void	init_plyr(t_info *info, t_map *map)
{
	int	y;
	int	x;

	find_start_position(map, &x, &y);
	info->p_x = x + 0.5;
	info->p_y = y + 0.5;
	info->p_orient = 42;
	if (map->map[y][x] == 'N')
		info->p_orient = M_PI + M_PI_2;
	else if (map->map[y][x] == 'E')
		info->p_orient = 0;
	else if (map->map[y][x] == 'S')
		info->p_orient = M_PI_2;
	else if (map->map[y][x] == 'W')
		info->p_orient = M_PI;
	else
	{
		ft_putstr_fd("Could not set player orientation\n", 2);
		exit(1);
	}
}
