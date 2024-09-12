/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:13:27 by tparratt          #+#    #+#             */
/*   Updated: 2024/09/12 14:19:32 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// checks if all remaining lines are whitespace
static int	all_remaining(int i, char **arr)
{
	while (arr[i])
	{
		if (!all_whitespace(arr[i]))
			return (0);
		i++;
	}
	return (1);
}

// determines if there are any empty lines within the map element
static void	find_empty_line(t_map *map)
{
	int	i;

	i = 0;
	while (map->map[i])
	{
		if (all_whitespace(map->map[i]) && !all_remaining(i, map->map))
			print_error("Empty line within map", map);
		i++;
	}
}

static void	check_textures(char *texture, t_map *map)
{
	int	fd;

	if (invalid_file_extension(texture, ".png"))
		print_error("Texture should be a file and have .png extension", map);
	fd = open(texture, O_RDONLY);
	if (fd == -1)
		print_error(NULL, NULL);
}

void	validate(t_map *map)
{
	check_textures(map->no, map);
	check_textures(map->so, map);
	check_textures(map->ea, map);
	check_textures(map->we, map);
	find_empty_line(map);
	check_chars(map);
	check_walls(map);
}
