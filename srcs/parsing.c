/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:12:47 by tparratt          #+#    #+#             */
/*   Updated: 2024/09/12 11:11:50 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// determines whether a line is; (0) a non-map element, (1) an empty line, (3) part of map element
static int	identify_line(char *line)
{
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2) || !ft_strncmp(line, "EA", 2) || !ft_strncmp(line, "WE", 2)
        || !ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
			return (0);
	else if (!ft_strncmp(line, "\n", 1) || all_whitespace(line))
        	return (1);
	else
        	return (2);
}

static int	*set(char **str_arr, t_map *map, int *int_arr)
{
	int	i;
	int	j;

	i = 0;
	while (str_arr[i])
	{
		int_arr[i] = ft_atoi(str_arr[i]);
		j = 0;
		while (str_arr[i][j])
		{
			if (ft_isalpha(str_arr[i][j]) || (int_arr[i] < 0 || int_arr[i] > 255))
			{
				free_2d(str_arr);
				free(int_arr);
				print_error("RGB contains alphabets or integer not in correct range", map);
			}
			j++;
		}
		i++;
	}
	return (int_arr);
}

// creates int array by atoi-ing each string in ceiling and floor
static int	*set_color_array(char *str, t_map *map)
{
	char	**str_arr;
	int	*int_arr;
	int	len;

	str_arr = ft_split(str, ',');
	if (!str_arr)
		print_error("Memory allocation failure", map);
	len = len_2d(str_arr);
	if (len >= 3)
	{
		free_2d(str_arr);
		print_error("RGB contains too many integers", map);
	}
	int_arr = (int *)malloc(3 * sizeof(int));
	if (!int_arr)
		print_error("Memory allocation failure", map);
	int_arr = set(str_arr, map, int_arr);
	free_2d(str_arr);
	return (int_arr);
}

// checks that all necessary elements are present in map struct
static void	all_elements_present(t_map *map)
{
	if (!map->no || !map->so || !map->ea || !map->we || !map->f || !map->c)
		print_error("Not all elements present", map);
	if (!map->map[0])
		print_error("No map present", map);
}

static int	*set_color(char *str, char **arr, t_map *map)
{
	int	*res;
    
	str = ft_strdup_mod(arr[1]);
	if (!str)
		print_error("Memory allocation failure", map);
	res = set_color_array(str, map);
	if (!res)
		print_error("Memory allocation failure", map);
	free(str);
	return (res);
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
static int	file_to_map(t_map *map, int i, char *line)
{
	static int	flag;
    
	if (identify_line(line) == 2 || (i && identify_line(line) == 1)) // to add also empty lines within the map
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

// adds information to map struct from input file
static void	set_initial_map(char *arg, t_map *map)
{
	int		fd;
	char		*line;
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

// returns the number of lines in the map element of the input file
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
		if ((identify_line(line) == 2) || (no_of_lines && identify_line(line) == 1))
			no_of_lines++;
	}
	close(fd);
	return (no_of_lines);
}

// returns map width by returning the length of the longest string in the map
// static size_t   map_width(t_map *map)
// {
//     int     i;
//     size_t  len;

//     i = 0;
//     len = 0;
//     while (map->map[i])
//     {
//         if (len < ft_strlen(map->map[i]))
//             len = ft_strlen(map->map[i]);
//         i++;
//     }
//     return (len);
// }

static int	longest_str_i(t_map *map)
{
	int	i;
	int	longest_index;
	size_t	max_len;
	size_t	current_len;

	i = 0;
	max_len = 0;
	longest_index = -1;
	while (map->map[i])
	{
		current_len = ft_strlen(map->map[i]);
		if (current_len > max_len)
		{
			max_len = current_len;
			longest_index = i;
		}
		i++;
	}
	return (longest_index);
}

static size_t	map_width(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (str[i] == ' ')
		i--;
	i++;
	return (i);
}

// returns the string of spaces to be added any strings in the map that are shorter than the longest string in the map
static char	*get_s2(size_t len, char *s1, t_map *map)
{
	int	i;
	char	*str;
	
	i = 0;
	str = malloc((len - ft_strlen(s1)) * sizeof(char) + 1);
	if (!str)
		print_error("Memory allocation failure", map);
	while (i < (len - ft_strlen(s1)))
	{
		str[i] = ' ';
		i++;
	}
	str[i] = '\0';
	return (str);
}

static void	add_s2(int width, char *s1, t_map *map, int i)
{
	char	*s2;
	char	*temp;
    
	s2 = get_s2(width, s1, map);
	temp = ft_strjoin(s1, s2);
	if (!temp)
		print_error("Memory allocation failure", map);
	free(map->map[i]);
	map->map[i] = ft_strdup(temp);
	if (!map->map[i])
		print_error("Memory allocation failure", map);
	free(temp);
	free(s1);
	free(s2);
}

// sets the final map->map 2d array
static void	set_final(t_map *map)
{
    int		i;
    size_t	width;
    int		idx;
    char	*s1;

    idx = longest_str_i(map);
    width = map_width(map->map[idx]);
    i = 0;
    while (map->map[i])
    {
	    if (i == idx)
	    {
		    s1 = ft_substr(map->map[idx], 0, width);
		    if (!s1)
			    print_error("Memory allocation failure", map);
	    }
	    else if (ft_strlen(map->map[i]) <= width) // is this needed?
		{
			s1 = ft_strdup(map->map[i]);
			if (!s1)
				print_error("Memory allocation failure", map);
		}
	    add_s2(width, s1, map, i);
	    i++;
    }
}

// initializes all map struct elements to NULL
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
	map->map = malloc((no_of_lines * sizeof(char *)) + 1);
	while (i < no_of_lines)
	{
		map->map[i] = NULL;
		i++;
	}
}

void	parse(char **argv, t_map *map)
{
	int	no_of_lines;
    
	if (invalid_file_extension(argv[1], ".cub"))
		print_error("Map should not be a directory and should have .cub file extension", NULL);
	no_of_lines = map_line_count(argv[1]);
	elements_to_null(map, no_of_lines);
	set_initial_map(argv[1], map);
	set_final(map);
}
