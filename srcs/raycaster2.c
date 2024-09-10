/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:46:43 by rboudwin          #+#    #+#             */
/*   Updated: 2024/09/10 11:51:18 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void raycaster(mlx_t *mlx, t_map *map, t_images *img, t_info *info)
{
    double ray_len;
    double ray_x_len;
    double ray_y_len;
    info->ray_x = info->p_x;
    info->ray_y = info->p_y;
    info->ray_orient = info->p_orient - (M_PI / 4);
    ray_len = 0;
    printf("first ray_orient is %f\n", info->ray_orient);
    printf("Initial ray start position is x: %f y:%f", info->ray_x, info->ray_y);
    
    while (ray_len < info->rend_dist)
    {
        ray_len += 0.01;
        //ray_len is hypoteneuse
        info->ray_x += (cos(info->ray_orient) * ray_len);
		info->ray_y += (sin(info->ray_orient) * ray_len);
        if (detect_square(map, info->ray_x, info->ray_y) == 1)
            break;
    }
    /*
        So we know our current position, and angle.
        we know our dx dy from the grid square. but depending on the angle we don't know which one comes first. so
        we need to increment .01 each time probably, until we hit the first intersection
    */
    //check horizontal intersections
    //check vertical intersections
}   