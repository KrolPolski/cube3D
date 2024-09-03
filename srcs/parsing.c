/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:12:47 by tparratt          #+#    #+#             */
/*   Updated: 2024/09/03 10:27:08 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

static int  *set_color_array(char *str, t_map *map)
{
    int     i;
    int     j;
    char    **str_arr;
    int     *int_arr;
    int     len;

    i = 0;
    str_arr = ft_split(str, ',');
    if (!str_arr)
    {
        free_map(map);
        print_error("Memory allocation failure");
    }
    len = len_2d(str_arr);
    if (len >= 3)
    {
        free_2d(str_arr);
        free_map(map);
        print_error("RGB contains too many integers");
    }
    int_arr = (int *)malloc(3 * sizeof(int));
    if (!int_arr)
    {
        free_map(map);
        print_error("Memory allocation failure");
    }
    while (str_arr[i])
    {
        j = 0;
        while (str_arr[i][j])
        {
            if (ft_isalpha(str_arr[i][j]))
            {
                free_2d(str_arr);
                free_map(map);
                print_error("RGB contains alphabets");
            }
            j++;
        }
        int_arr[i] = ft_atoi(str_arr[i]);
        if (int_arr[i] < 0 || int_arr[i] > 255)
        {
            free_2d(str_arr);
            free(int_arr);
            free_map(map);
            print_error("RGB integer not in correct range");
        }
        i++;
    }
    free_2d(str_arr);
    return (int_arr);
}

static void all_elements_present(t_map *map)
{
    if (!map->no || !map->so || !map->ea || !map->we || !map->f || !map->c)
    {
        free_map(map);
        print_error("Not all elements present");
    }
}

static int file_to_map(t_map *map, int i, char *line)
{
    char        **arr;
    static int  flag;

    if (identify_line(line) == 2 || (i && identify_line(line) == 1)) // to add also empty lines within the map
    {
        flag = 1;
        map->map[i] = ft_strdup_mod(line);
        if (!map->map[i])
        {
            free_map(map);
            print_error("Memory allocation failure");
        }
        i++;
    }
    else if (identify_line(line) == 0)
    {
        if (flag != 1)
        {
            arr = ft_split(line, ' ');
            if (!arr)
            {
                free_map(map);
                print_error("Memory allocation failure");
            }
            if (!ft_strncmp(arr[0], "NO", 2))
            {
                map->no = ft_strdup_mod(arr[1]);
                {
                    free_map(map);
                    print_error("Memory allocation failure");
                }
            }
            if (!ft_strncmp(arr[0], "SO", 2))
            {
                map->so = ft_strdup_mod(arr[1]);
                {
                    free_map(map);
                    print_error("Memory allocation failure");
                }
            }
            if (!ft_strncmp(arr[0], "EA", 2))
            {
                map->ea = ft_strdup_mod(arr[1]);
                {
                    free_map(map);
                    print_error("Memory allocation failure");
                }
            }
            if (!ft_strncmp(arr[0], "WE", 2))
            {
                map->we = ft_strdup_mod(arr[1]);
                {
                    free_map(map);
                    print_error("Memory allocation failure");
                }
            }
            if (!ft_strncmp(arr[0], "F", 1))
            {
                map->floor = ft_strdup_mod(arr[1]);
                {
                    free_map(map);
                    print_error("Memory allocation failure");
                }
                map->f = set_color_array(map->floor, map);
                {
                    free_map(map);
                    print_error("Memory allocation failure");
                } 
            }
            if (!ft_strncmp(arr[0], "C", 2))
            {
                map->ceiling = ft_strdup_mod(arr[1]);
                {
                    free_map(map);
                    print_error("Memory allocation failure");
                }    
                map->c = set_color_array(map->ceiling, map);
                {
                    free_map(map);
                    print_error("Memory allocation failure");
                }
            }
            free_2d(arr);
        }
        else
        {
            free_map(map);
            print_error("Elements must appear before map content");
        }
    }
    return (i);
}

void set_initial_map(char *arg, t_map *map)
{
    int     fd;
    char    *line;
    int     i;
    
    fd = open(arg, O_RDONLY);
    if (fd == -1)
        print_error("Cannot open file");
    i = 0;
    line = get_next_line(fd);
    if (!line)
        print_error("gnl error");
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

int  map_line_count(char *arg)
{
    int     fd;
    char    *line;
    int     no_of_lines;
    
    fd = open(arg, O_RDONLY);
    if (fd == -1)
        print_error("Cannot open file");
    line = get_next_line(fd);
    if (!line)
        print_error("gnl error");
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

static size_t   get_longest_len(t_map *map)
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

static char *get_s2(size_t len, char *s1, t_map *map)
{
    size_t  i;
    char    *str;

    i = 0;
    str = malloc((len - ft_strlen(s1)) * sizeof(char) + 1);
    if (!str)
    {
        free_map(map);
        print_error("Memory allocation failure");
    }
    while (i < (len - ft_strlen(s1)))
    {
        str[i] = ' ';
        i++;
    }
    str[i] = '\0';
    return (str);
}

void set_final(t_map *map)
{
    int     i;
    size_t  len;
    char    *s1;
    char    *s2;
    char    *temp;

    len = get_longest_len(map);
    i = 0;
    while (map->map[i])
    {
        if (ft_strlen(map->map[i]) < len)
        {
            s1 = ft_strdup(map->map[i]);
            if (!s1)
            {
                free_map(map);
                print_error("Memory allocation failure");
            }
            s2 = get_s2(len, s1, map);
            temp = ft_strjoin(s1, s2);
            {
                free_map(map);
                print_error("Memory allocation failure");
            }
            free(map->map[i]);
            map->map[i] = ft_strdup(temp);
            {
                free_map(map);
                print_error("Memory allocation failure");
            }
            free(temp);
            free(s1);
            free(s2);
        }
        i++;
    }
}