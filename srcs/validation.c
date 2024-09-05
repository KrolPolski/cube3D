/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:13:27 by tparratt          #+#    #+#             */
/*   Updated: 2024/09/05 12:10:43 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int  invalid_file_extension(char *arg, char *ext)
{
    char    *str;
    int     i;

    str = ft_strchr(arg, '.');
    if (str == NULL || ft_strncmp(str, ext, 5))
        return (1);
    return (0);
}

static void valid_chars(char c, t_map *map)
{
    if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != ' ')
        print_error("Invalid map character(s)", map);
}

static int start_positions(char c, int player_count, t_map *map)
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
static void check_chars(t_map *map)
{
    int i;
    int j;
    int player_count;

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

// checks if all remaining lines are whitespace
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

// determines if there are any empty lines within the map element
static void find_empty_line(t_map *map)
{
    int i;

    i = 0;
    while (map->map[i])
    {
        if (all_whitespace(map->map[i]) && !all_remaining(i, map->map))
            print_error("Empty line within map", map);
        i++;
    }
}

static void check_textures(t_map *map)
{
    ft_putendl_fd(map->no, 1);
    if (invalid_file_extension(map->no, ".png"))
        print_error("Texture should have .png file extension", map);
}

void    validate(t_map *map)
{
    check_textures(map);
    find_empty_line(map);
    check_chars(map);
    check_walls(map);
}
