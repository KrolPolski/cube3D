/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:12:47 by tparratt          #+#    #+#             */
/*   Updated: 2024/10/23 11:08:41 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* returns the number of lines in the map element of the input file */
static int	map_line_count(char *arg)
{
	int		fd;
	char	*line;
	int		no_of_lines;

	fd = open(arg, O_RDONLY);
	if (fd == -1)
		print_error(NULL, NULL);
	line = get_next_line(fd);
	if (!line)
		print_error("Empty file", NULL);
	no_of_lines = 0;
	if (identify_line(line) == 2)
		no_of_lines++;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		if ((identify_line(line) == 2) || (no_of_lines
				&& identify_line(line) == 1))
			no_of_lines++;
	}
	close(fd);
	return (no_of_lines);
}

/* checks that all necessary elements are present in map struct */
static void	all_elements_present(t_map *map)
{
	if (!map->no || !map->so || !map->ea || !map->we || !map->f || !map->c)
		print_error("Not all elements present", map);
	if (!map->map[0])
		print_error("No map present", map);
}

/* adds information to map struct from input file */
static void	set_initial_map(char *arg, t_map *map)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(arg, O_RDONLY);
	if (fd == -1)
		print_error(NULL, NULL);
	i = 0;
	line = get_next_line(fd);
	if (!line)
		print_error("gnl error", map);
	i = file_to_map(map, i, line);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (!line)
			break ;
		i = file_to_map(map, i, line);
	}
	map->map[i] = NULL;
	all_elements_present(map);
	close(fd);
}

/* initializes all map struct elements to NULL */
static void	elements_to_null(t_map *map, int no_of_lines)
{
	int	i;

	i = 0;
	map->no = NULL;
	map->so = NULL;
	map->ea = NULL;
	map->we = NULL;
	map->floor = NULL;
	map->ceiling = NULL;
	map->f = NULL;
	map->c = NULL;
	map->map = malloc((no_of_lines + 1) * sizeof(char *));
	if (map->map == NULL)
		print_error("Memory allocation failed", map);
	while (i < no_of_lines)
	{
		map->map[i] = NULL;
		i++;
	}
}

void	parse(char **argv, t_map *map)
{
	int	no_of_lines;

	if (invalid_file_extension(argv[1], ".cub", ".CUB"))
		print_error("Map should be a file and have .cub extension", NULL);
	no_of_lines = map_line_count(argv[1]);
	elements_to_null(map, no_of_lines);
	set_initial_map(argv[1], map);
	set_final(map);
}
