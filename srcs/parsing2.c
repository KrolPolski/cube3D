/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:03:02 by tparratt          #+#    #+#             */
/*   Updated: 2024/09/12 13:23:39 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// determines whether a line is; (0) a non-map element, (1) an empty line,(3) part of map element
int	identify_line(char *line)
{
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "EA", 2) || !ft_strncmp(line, "WE", 2)
		|| !ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
		return (0);
	else if (!ft_strncmp(line, "\n", 1) || all_whitespace(line))
		return (1);
	else
		return (2);
}

static char	*set_texture(char **arr, t_map *map)
{
	char	*res;

	res = ft_strdup_mod(arr[1]);
	if (!res)
		print_error("Memory allocation failure", map);
	return (res);
}

static char	*determine_then_set(char **arr, char *name, char *str, t_map *map)
{
	if (!ft_strncmp(arr[0], name, 2))
	{
		if (str)
			print_error("More than one NO element in file", map);
		str = set_texture(arr, map);
	}
	return (str);
}

static void	set_elements(char *line, t_map *map)
{
	char	**arr;

	arr = ft_split(line, ' ');
	if (len_2d(arr) > 1)
		print_error("Element information should not contain spaces", map);
	if (!arr)
		print_error("Memory allocation failure", map);
	map->no = determine_then_set(arr, "NO", map->no, map);
	map->so = determine_then_set(arr, "SO", map->so, map);
	map->ea = determine_then_set(arr, "EA", map->ea, map);
	map->we = determine_then_set(arr, "WE", map->we, map);
	if (!ft_strncmp(arr[0], "F", 1))
	{
		if (map->f)
			print_error("More than one F element in file", map);
		map->f = set_color(map->floor, arr, map);
	}
	if (!ft_strncmp(arr[0], "C", 2))
	{
		if (map->c)
			print_error("More than one C element in file", map);
		map->c = set_color(map->ceiling, arr, map);
	}
	free_2d(arr);
}

// intializes one line to map struct
int file_to_map(t_map *map, int i, char *line)
{
	static int	flag;

	if (identify_line(line) == 2 || (i && identify_line(line) == 1))
		// to add also empty lines within the map
	{
		flag = 1;
		map->map[i] = ft_strdup_mod(line);
		if (!map->map[i])
			print_error("Memory allocation failure", map);
		i++;
	}
	else if (identify_line(line) == 0)
	{
		if (flag != 1)
			set_elements(line, map);
		else
		{
			map->map[i] = NULL;
			print_error("Elements must appear before map content", map);
		}
	}
	return (i);
}
