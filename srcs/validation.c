/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:13:27 by tparratt          #+#    #+#             */
/*   Updated: 2024/08/28 14:55:42 by tparratt         ###   ########.fr       */
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
        if (all_whitespace(arr[i]))
            return (0);
        i++;
    }
    return (1);
}

void    validate(t_map *map)
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