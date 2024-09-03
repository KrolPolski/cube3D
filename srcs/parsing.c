/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:12:47 by tparratt          #+#    #+#             */
/*   Updated: 2024/09/03 14:25:20 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// determines whether a line is; (0) a non-map element, (1) an empty line, (3) part of map element
static int identify_line(char *line)
{
    if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2) || !ft_strncmp(line, "EA", 2) || !ft_strncmp(line, "WE", 2) ||
            !ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
        return (0);
    else if (!ft_strncmp(line, "\n", 1))
        return (1);
    else
        return (2);
}

static int  *set(char **str_arr, t_map *map, int *int_arr)
{
    int i;
    int j;

    i = 0;
    while (str_arr[i])
    {
        j = 0;
        while (str_arr[i][j])
        {
            if (ft_isalpha(str_arr[i][j]))
            {
                free_2d(str_arr);
                print_error("RGB contains alphabets", map);
            }
            j++;
        }
        int_arr[i] = ft_atoi(str_arr[i]);
        if (int_arr[i] < 0 || int_arr[i] > 255)
        {
            free_2d(str_arr);
            free(int_arr);
            print_error("RGB integer not in correct range", map);
        }
        i++;
    }
    return (int_arr);
}

// creates int array by atoi-ing each string in ceiling and floor
static int  *set_color_array(char *str, t_map *map)
{
    char    **str_arr;
    int     *int_arr;
    int     len;

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
static void all_elements_present(t_map *map)
{
    if (!map->no || !map->so || !map->ea || !map->we || !map->f || !map->c)
        print_error("Not all elements present", map);
}

// intializes one line to map struct
static int file_to_map(t_map *map, int i, char *line)
{
    char        **arr;
    static int  flag;

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
        {
            arr = ft_split(line, ' ');
            if (!arr)
                print_error("Memory allocation failure", map);
            if (!ft_strncmp(arr[0], "NO", 2))
            {
                map->no = ft_strdup_mod(arr[1]);
                if (!map->no)
                    print_error("Memory allocation failure", map);
            }
            if (!ft_strncmp(arr[0], "SO", 2))
            {
                map->so = ft_strdup_mod(arr[1]);
                if (!map->so)
                    print_error("Memory allocation failure", map);
            }
            if (!ft_strncmp(arr[0], "EA", 2))
            {
                map->ea = ft_strdup_mod(arr[1]);
                if (!map->ea)
                    print_error("Memory allocation failure", map);
            }
            if (!ft_strncmp(arr[0], "WE", 2))
            {
                map->we = ft_strdup_mod(arr[1]);
                if (!map->we)
                    print_error("Memory allocation failure", map);
            }
            if (!ft_strncmp(arr[0], "F", 1))
            {
                map->floor = ft_strdup_mod(arr[1]);
                if (!map->floor)
                    print_error("Memory allocation failure", map);
                map->f = set_color_array(map->floor, map);
                if (!map->f)
                    print_error("Memory allocation failure", map);
            }
            if (!ft_strncmp(arr[0], "C", 2))
            {
                map->ceiling = ft_strdup_mod(arr[1]);
                if (!map->ceiling)
                    print_error("Memory allocation failure", map); 
                map->c = set_color_array(map->ceiling, map);
                if (!map->c)
                    print_error("Memory allocation failure", map);
            }
            free_2d(arr);
        }
        else
            print_error("Elements must appear before map content", map);
    }
    return (i);
}

// adds information to map struct from input file
void set_initial_map(char *arg, t_map *map)
{
    int     fd;
    char    *line;
    int     i;
    
    fd = open(arg, O_RDONLY);
    if (fd == -1)
        print_error("Cannot open file", map);
    i = 0;
    line = get_next_line(fd);
    if (!line)
        print_error("gnl error", map);
    i = file_to_map(map, i, line);
    while (line)
    {
        free(line);
        line = get_next_line(fd);
        if (!line) // What if we have malloc failure here?
            break ;
        i = file_to_map(map, i, line);
    }
    map->map[i] = NULL;
    all_elements_present(map);
    close(fd);
}

// returns the number of lines in the map element of the input file
int  map_line_count(char *arg)
{
    int     fd;
    char    *line;
    int     no_of_lines;
    
    fd = open(arg, O_RDONLY);
    if (fd == -1)
        print_error("Cannot open file", NULL); // check this works with map as NULL
    line = get_next_line(fd);
    if (!line)
        print_error("gnl error", NULL);
    no_of_lines = 0;
    if (identify_line(line) == 2)
        no_of_lines++;
    while (line)
    {
        free(line);
        line = get_next_line(fd);
        if (!line) // What if we have malloc failure here?
            break ;
        if ((identify_line(line) == 2) || (no_of_lines && identify_line(line) == 1))
            no_of_lines++;
    }
    close(fd);
    return (no_of_lines);
}

// returns map width by finding longest string in the map
static size_t   map_width(t_map *map)
{
    int     i;
    size_t  len;

    i = 0;
    len = 0;
    while (map->map[i])
    {
        if (len < ft_strlen(map->map[i]))
            len = ft_strlen(map->map[i]);
        i++;
    }
    return (len);
}

// returns the string of spaces to be added any strings in the map that are shorter than the longest string in the map
static char *get_s2(size_t len, char *s1, t_map *map)
{
    size_t  i;
    char    *str;

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

// sets the final map->map 2d array
void set_final(t_map *map)
{
    int     i;
    size_t  width;
    char    *s1;
    char    *s2;
    char    *temp;

    width = map_width(map);
    i = 0;
    while (map->map[i])
    {
        if (ft_strlen(map->map[i]) < width)
        {
            s1 = ft_strdup(map->map[i]);
            if (!s1)
                print_error("Memory allocation failure", map);
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
        i++;
    }
}

// initializes all map struct elements to NULL
static void elements_to_null(t_map *map, int no_of_lines)
{
    int i;

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

void    parse(char **argv, t_map *map)
{
    int     no_of_lines;
    
    check_file_extension(argv[1]);
    no_of_lines = map_line_count(argv[1]);
    elements_to_null(map, no_of_lines);
    set_initial_map(argv[1], map);
    set_final(map);
}