/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:30:49 by tparratt          #+#    #+#             */
/*   Updated: 2024/10/22 13:22:12 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Returns 1 if the file extension is invalid or doesn't exist */
int	invalid_file_extension(char *arg, char *lower, char *upper)
{
	char	*str;

	str = ft_strchr_rev(arg, '.');
	if (str == NULL)
		return (1);
	if (ft_strncmp(str, lower, ft_strlen(lower)) != 0
		&& ft_strncmp(str, upper, ft_strlen(upper)) != 0)
		return (1);
	return (0);
}

static void	valid_chars(char c, t_map *map)
{
	if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W'
		&& c != ' ')
		print_error("Invalid map character(s)", map);
}

static int	start_positions(char c, int player_count, t_map *map)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		player_count++;
		if (player_count > 1)
			print_error("More than one start position", map);
	}
	return (player_count);
}

// determines whether or not the map element contains all valid characters
void	check_chars(t_map *map)
{
	int	i;
	int	j;
	int	player_count;

	i = 0;
	player_count = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			player_count = start_positions(map->map[i][j], player_count, map);
			valid_chars(map->map[i][j], map);
			j++;
		}
		i++;
	}
	if (player_count == 0)
		print_error("No start position", map);
}
