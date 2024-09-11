/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:46:43 by rboudwin          #+#    #+#             */
/*   Updated: 2024/09/11 14:16:28 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double find_first_horizontal(mlx_t *mlx, t_map *map, t_info *info)
{
    double delta_x;
    double delta_y;
    double previous_position;
    double len;
    
    //we will know y but not x
    previous_position = info->ray_y;
    if (info->ray_orient > M_PI)
        info->horiz_vec[1] = floorf(info->ray_y);
    else
        info->horiz_vec[1] = ceilf(info->ray_y);
    delta_y = info->horiz_vec[1] - previous_position;
    
    printf("So our first horizontal intersection is at y: %f\n", info->ray_y);
    printf("Delta Y: %f\n", delta_y);
   //protecting from undefined results
    if ((info->ray_orient > M_PI_2 - 0.1 && info->ray_orient < M_PI_2 + 0.1) ||
            (info->ray_orient > (M_PI * 1.5 - 0.1) && info->ray_orient < (M_PI * 1.5 + 0.1)))
        delta_x = 0;
    else        
        delta_x = delta_y * tan(info->ray_orient);
    printf("Delta X: %f\n", delta_x);
    info->horiz_vec[0] = info->ray_x + delta_x;
    printf("So we will use the following vector (x,y): (%f, %f)\n", info->horiz_vec[0], info->horiz_vec[1]);
    len = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
    printf("The length is %f\n", len);
    return len;
    //this doesn't work because sometimes delta_x or y is 0.
}

 void check_radian_overflow(t_info *info)
 {
    if (info->ray_orient > 2 * M_PI)
        info->ray_orient -= 2 * M_PI;
    else if (info->ray_orient < 0)
        info->ray_orient += 2 * M_PI;
    else
        return;
 }


void raycaster(mlx_t *mlx, t_map *map, t_images *img, t_info *info)
{
    double ray_len;
    double ray_x_len;
    double ray_y_len;
    double horiz_len;
    double verti_len;
    info->ray_x = info->p_x;
    info->ray_y = info->p_y;
    info->ray_orient = info->p_orient - (M_PI / 6);
    check_radian_overflow(info);
    ray_len = 0;
    printf("first ray_orient is %f\n", info->ray_orient);
    printf("Initial ray start position is x: %f y:%f\n", info->ray_x, info->ray_y);
    
    horiz_len = find_first_horizontal(mlx, map, info);
    /*
        So we know our current position, and angle.
        we know our dx dy from the grid square. but depending on the angle we don't know which one comes first. so
        we need to increment .01 each time probably, until we hit the first intersection
    */
    //check horizontal intersections
    //check vertical intersections
}   