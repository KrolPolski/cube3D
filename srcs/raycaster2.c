/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:46:43 by rboudwin          #+#    #+#             */
/*   Updated: 2024/10/14 11:49:53 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double find_first_vertical(mlx_t *mlx, t_map *map, t_info *info)
{
    double delta_x;
    double delta_y;
    double previous_position;
    double len;
    
    //we will know x but not y
    previous_position = info->ray_x;
    if (info->ray_orient >= M_PI_2 && info->ray_orient < 3 * M_PI_2)
        info->verti_vec[0] = floorf(info->ray_x);
    else
        info->verti_vec[0] = ceilf(info->ray_x);
    if (info->ray_orient >= M_PI_2 && info->ray_orient < 3 * M_PI_2) {
    // Ray moving left
        delta_x = -fabs(info->verti_vec[0] - info->ray_x);
     } else 
         {
    // Ray moving right
    delta_x = fabs(info->verti_vec[0] - info->ray_x);}   
    printf("So our first vertical intersection is at x: %f\n", info->verti_vec[0]);
    printf("Delta X: %f\n", delta_x);
   //protecting from undefined results, need to adjust this
    if (fabs(sin(info->ray_orient) < EPSILON))
        delta_y = 0;
    else        
    {
        if (info->ray_orient > M_PI)  // Ray moving up
            delta_y = -fabs(delta_x) / tan(info->ray_orient);
        else  // Ray moving down
            delta_y = fabs(delta_x) / tan(info->ray_orient);}
    printf("Delta y: %f\n", delta_y);
    info->verti_vec[1] = info->ray_y + delta_y;
    printf("So we will use the following vector (x,y): (%f, %f)\n", info->verti_vec[0], info->verti_vec[1]);
    len = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
    printf("The length is %f\n", len);
    return len;
    //this doesn't work because sometimes delta_x or y is 0.
}
double find_next_vertical(mlx_t *mlx, t_map *map, t_info(*info), double len)
{
    double delta_y;
    double delta_x;
    
    if (info->ray_orient > M_PI_2 && info->ray_orient < M_PI_2 * 3)
        delta_x = -1.0;
    else
        delta_x = 1.0;
    if (fabs(sin(info->ray_orient)) < EPSILON)
        delta_y = 0;
    else
    {
        if (info->ray_orient > M_PI)  // Ray moving up
            delta_y = -fabs(tan(info->ray_orient));
        else  // Ray moving down
            delta_y = fabs(tan(info->ray_orient));
    }
    info->verti_vec[0] = info->verti_vec[0] + delta_x;
    info->verti_vec[1] = info->verti_vec[1] + delta_y;
    printf("new verti_vec: %f, %f\n", info->verti_vec[0], info->verti_vec[1]);
    len += sqrt(pow(delta_x, 2) + pow(delta_y, 2));
    return len;
}
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
  if (info->ray_orient > 0 && info->ray_orient > M_PI) {
    // Ray moving up
    delta_y = -fabs(info->horiz_vec[1] - info->ray_y);
} else {
    // Ray moving down
    delta_y = fabs(info->horiz_vec[1] - info->ray_y);
}
    
    printf("So our first horizontal intersection is at y: %f\n", info->horiz_vec[1]);
    printf("Delta Y: %f\n", delta_y);
   //protecting from undefined results
    if (fabs(cos(info->ray_orient)) < EPSILON)
        delta_x = 0;
    else        
    {
        if (info->ray_orient < M_PI_2 || info->ray_orient > M_PI * 1.5)
            delta_x = fabs(delta_y / tan(info->ray_orient)); 
        else 
            delta_x = -fabs(delta_y / tan(info->ray_orient)); 
    }
    printf("Delta X: %f\n", delta_x);
    info->horiz_vec[0] = info->ray_x + delta_x;
    printf("So we will use the following vector (x,y): (%f, %f)\n", info->horiz_vec[0], info->horiz_vec[1]);
    len = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
    printf("The length is %f\n", len);
    return len;
    //this doesn't work because sometimes delta_x or y is 0.
}
double  find_next_horizontal(mlx_t *mlx, t_map *map, t_info *info, double len)
{
    double delta_y;
    double delta_x;
    double x_candidate;
    double y_candidate;
    
    if (info->ray_orient > M_PI)
        delta_y = -1.0;
    else
        delta_y = 1.0;
    if (fabs(cos(info->ray_orient)) < EPSILON)
        delta_x = 0;
    else
    {
        if (info->ray_orient < M_PI_2 || info->ray_orient > M_PI * 1.5)
            delta_x = fabs(1.0 / tan(info->ray_orient));
        else
            delta_x = -fabs(1.0 / tan(info->ray_orient));
    }
    info->horiz_vec[0] = info->horiz_vec[0] + delta_x;
    info->horiz_vec[1] = info->horiz_vec[1] + delta_y;
    printf("new horiz_vec: %f, %f\n", info->horiz_vec[0], info->horiz_vec[1]);
    len += sqrt(pow(delta_x, 2) + pow(delta_y, 2));
    return len;
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

int get_wall_color(double ray_orient, enum e_intersect inter)
{
    /* North = red
        South = green
        East = blue
        West = yellow
    */ 
    if (inter == horizontal)
    {
        if (ray_orient >= M_PI)
            return (get_rgba(0,255,0,255));
        else
            return (get_rgba(255,0,0,255));
    }
    else if (inter == vertical)
    {
        if (ray_orient >= M_PI_2 && ray_orient < (M_PI * 1.5))
            return (get_rgba(0, 0,255,255));
        else
            return (get_rgba(255,255,0,255));
    }
    return (get_rgba(244, 244, 244, 255));
}

void cast_wall(double ray_len, int i, t_info *info, t_images *img, enum e_intersect inter)
{
    int top_pixel;
    int pixels;
    int color;
    float angle;
    unsigned int column_height;
    int proj_plane_dist;

    printf("Inside cast_wall, inter is %d\n", inter);
    proj_plane_dist = (info->s_width / 2) / tan(M_PI / 6);
    
    color = get_wall_color(info->ray_orient, inter);
    //check to see if we hit the max render distance already
    if (ray_len > info->rend_dist)
        return ;
    top_pixel = 0;
    pixels = 0;
    column_height = (info->s_height / (ray_len  * cos(info->ray_orient - info->p_orient)));
    top_pixel = info->s_height / 2 - column_height / 2;
    if (top_pixel < 0)
        top_pixel = 0;
    printf("We are trying to draw a column at x: %d\n", i);
    while (pixels < column_height - 1)
    {
        if (top_pixel + pixels > info->s_height - 1 || top_pixel + pixels < 0 || i > info->s_width || i < 0)
        {
            printf("tried to draw out of bounds\n");
            break;
        }
        mlx_put_pixel(img->world, i, top_pixel + pixels, color);
        pixels++;
    }
    
}
void raycaster(mlx_t *mlx, t_map *map, t_images *img, t_info *info)
{
    double ray_len;
    double ray_x_len;
    double ray_y_len;
    double horiz_len;
    double verti_len;
    double len_parking;
    info->ray_x = info->p_x;
    info->ray_y = info->p_y;
    char ret;
    int i;
    enum e_intersect inter;
    
    info->ray_orient = info->p_orient - (M_PI / 6);
    mlx_delete_image(mlx, img->world);
    img->world = mlx_new_image(mlx, info->s_width, info->s_height);
    mlx_image_to_window(mlx, img->world, 0, 0);
    i = 0;
    while (i < info->s_width)
    {
        check_radian_overflow(info);
        ray_len = 0;
        info->ray_x = info->p_x;
        info->ray_y = info->p_y;
       // printf("first ray_orient is %f\n", info->ray_orient);
      //  printf("Initial ray start position is x: %f y:%f\n", info->ray_x, info->ray_y);
        
        horiz_len = find_first_horizontal(mlx, map, info);
        verti_len = find_first_vertical(mlx, map, info);
       // printf("We have received both lengths, they are:\n");
       // printf("horiz_len: %f \n", horiz_len);
     //   printf("verti_len: %f \n", verti_len);
        if (horiz_len < verti_len)
            ray_len = horiz_len;
        else
            ray_len = verti_len;
        printf("So the distance to the closest intersection is '%f'\n", ray_len);
        while (detect_square(map, info->horiz_vec[0], info->horiz_vec[1]) != '1')
        {
            horiz_len = find_next_horizontal(mlx, map, info, horiz_len);
            
            //ret = detect_square(map, info->horiz_vec[0], info->horiz_vec[1]);
            //printf("detect_square returned '%c'\n", ret);
        }
        while (detect_square(map, info->verti_vec[0], info->verti_vec[1]) != '1')
        {
            verti_len = find_next_vertical(mlx, map, info, verti_len);
        }
        if (horiz_len < verti_len)
        {
            ray_len = horiz_len;
            inter = horizontal;
        }
        else
        {
            ray_len = verti_len;
            inter = vertical;
        }
        printf("So horiz_len to a wall is %f\n", horiz_len);
        printf("and verti_len to a wall is %f\n", verti_len);
        printf("And the shorter of these two distances to a wall is %f\n", ray_len);
        cast_wall(ray_len, i, info, img, inter);
        i++;
        info->ray_orient += (M_PI / 3.0) * (1.0 / (double)info->s_width);
    }
}   