/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:13:27 by tparratt          #+#    #+#             */
/*   Updated: 2024/08/28 16:36:09 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int  check_file_extension(char *arg)
{
    char    *ext;
    
    ext = ft_strchr(arg, '.');
    if (ext == NULL || ft_strncmp(ext, ".cub", 5))
    {
        ft_putendl_fd("Error\nWrong file extension", 2);
        return (1);
    }
    return (0);
}

static int  all_remaining(int i, char **arr)
{
    while (arr[i])
    {
        if (!all_whitespace(arr[i]))
            return (0);
        i++;
    }
    return (1);
}

static void check_walls(t_map *map) //finish this
{
    int i;

    i = 0;
    while (map->map[0][i])
    {
        if (map->map[0][i] != '1' && map->map[0][i] != ' ')
        {
            ft_putendl_fd("Error\nMap not surrounded by walls", 2);
            exit(1);
        }
        i++;
    }
}

static void valid_chars(char c)
{
    if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != ' ')
    {
        ft_putendl_fd("Error\nInvalid map character(s)", 2);
        exit(1);
    }
}

static int start_positions(char c, int player_count)
{
    if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
    {
        player_count++;
        if (player_count > 1)
        {
            ft_putendl_fd("Error\nMore than one start position", 2);
            exit(1);
        }
    }
    return (player_count);
}

static void check_chars(t_map *map)
{
    int i;
    int j;
    int player_count;
    int empty_space_count;

    i = 0;
    player_count = 0;
    empty_space_count = 0;
    while (map->map[i])
    {
        j = 0;
        while (map->map[i][j])
        {
            if (map->map[i][j] == '0')
                empty_space_count++;
            player_count = start_positions(map->map[i][j], player_count);
            valid_chars(map->map[i][j]);
            j++;
        }
        i++;
    }
    if (player_count == 0)
    {
        ft_putendl_fd("Error\nNo start position", 2);
        exit(1);
    }
    if (empty_space_count == 0)
    {
        ft_putendl_fd("Error\nNo empty space", 2);
        exit(1);
    }
}

static void find_empty_line(t_map *map)
{
    int i;

    i = 0;
    while (map->map[i])
    {
        if (all_whitespace(map->map[i]) && !all_remaining(i, map->map))
        {
            ft_putendl_fd("Error\nEmpty line within map", 2);
            free_map(map);
            exit(1);
        }
        i++;
    }
}

void    validate(t_map *map)
{
    find_empty_line(map);
    check_chars(map);
    check_walls(map);
}