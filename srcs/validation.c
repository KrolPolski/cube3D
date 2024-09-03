/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:13:27 by tparratt          #+#    #+#             */
/*   Updated: 2024/09/03 11:16:22 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void  check_file_extension(char *arg)
{
    char    *ext;
    
    ext = ft_strchr(arg, '.');
    if (ext == NULL || ft_strncmp(ext, ".cub", 5))
        print_error("Memory allocation failure", NULL);
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

static void valid_chars(char c, t_map *map)
{
    if (c != '1' && c != '0' && c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != ' ')
        print_error("Memory allocation failure", map);
}

static int start_positions(char c, int player_count, t_map *map)
{
    if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
    {
        player_count++;
        if (player_count > 1)
            print_error("Memory allocation failure", map);
    }
    return (player_count);
}

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
        print_error("Memory allocation failure", map);
}

static void find_empty_line(t_map *map)
{
    int i;

    i = 0;
    while (map->map[i])
    {
        if (all_whitespace(map->map[i]) && !all_remaining(i, map->map))
            print_error("Memory allocation failure", map);
        i++;
    }
}

void    validate(t_map *map)
{
    find_empty_line(map);
    check_chars(map);
    check_walls(map);
}
