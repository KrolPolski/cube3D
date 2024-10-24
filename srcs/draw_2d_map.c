/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:31:09 by rboudwin          #+#    #+#             */
/*   Updated: 2024/10/24 08:18:13 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Draws background color on minimap */
void	map_background(t_map *map, t_info *info)
{
	int	i;
	int	j;

	i = 0;
	while (i < info->map_height)
	{
		j = 0;
		while (j < info->map_width)
		{
			mlx_put_pixel(info->img->map, j, i, get_rgba(map->c[0],
					map->c[1], map->c[2], 0));
			j++;
		}
		i++;
	}
}

/* draws the field of view markers on minimap */
void	draw_fov(t_info *info, int px_x, int px_y)
{
	int	i;
	int	ray_x;
	int	ray_y;

	i = 0;
	while (i < 30)
	{
		ray_x = px_x + round(i * cos(info->p_orient - M_PI / 6));
		ray_y = px_y + round(i * sin(info->p_orient - M_PI / 6));
		if (ray_x >= 0 && ray_y >= 0 && ray_x < (int)info->img->plyr->width
			&& ray_y < (int)info->img->plyr->height)
			mlx_put_pixel(info->img->plyr, ray_x, ray_y,
				get_rgba(255, 255, 0, 255));
		ray_x = px_x + round(i * cos(info->p_orient + M_PI / 6));
		ray_y = px_y + round(i * sin(info->p_orient + M_PI / 6));
		if (ray_x >= 0 && ray_y >= 0 && ray_x < (int)info->img->plyr->width
			&& ray_y < (int)info->img->plyr->height)
			mlx_put_pixel(info->img->plyr, ray_x, ray_y,
				get_rgba(255, 255, 0, 255));
		i++;
	}
}

/* Draws the player position on minimap */
void	draw_2d_player(t_map *map, t_info *info)
{
	int	px_x;
	int	px_y;
	int	i;
	int	k;

	px_x = info->p_x * map->sq;
	px_y = info->p_y * map->sq;
	i = 0;
	k = 0;
	ft_memset(info->img->plyr->pixels, 0, info->img->plyr->width
		* info->img->plyr->height * BPP);
	while (k < 10)
	{
		while (i < 10)
		{
			mlx_put_pixel(info->img->plyr, px_x + i, px_y + k,
				get_rgba(255, 0, 0, 255));
			i++;
		}
		i = 0;
		k++;
	}
	draw_fov(info, px_x + 5, px_y + 5);
}

/* creates img instances and draws minimap */
void	draw_2d_map(mlx_t *mlx, t_map *map, t_info *info)
{	
	mlx_image_to_window(info->mlx, info->img->map, 20, 20);
	map->x_len = 0;
	map->y_len = 0;
	map->x_len = ft_strlen(map->map[0]);
	while (map->map[map->y_len])
	{
		map->y_len++;
	}
	map->sq_w = info->map_width / map->x_len;
	map->sq_h = info->map_height / map->y_len;
	if (map->sq_w <= map->sq_h)
		map->sq = map->sq_w;
	else
		map->sq = map->sq_h;
	draw_squares(map, info);
	draw_2d_player(map, info);
	mlx_image_to_window(mlx, info->img->plyr, 20, 20);
}
