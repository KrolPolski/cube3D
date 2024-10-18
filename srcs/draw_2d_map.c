/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:31:09 by rboudwin          #+#    #+#             */
/*   Updated: 2024/10/18 12:31:57 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	map_background(mlx_t *mlx, t_map *map, t_info *info)
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

void	draw_squares(mlx_t *mlx, t_map *map, t_info *info)
{
	int	x;
	int	y;
	int	px_x;
	int	px_y;
	int	i;
	int	k;

	x = 0;
	y = 0;
	i = 0;
	k = 0;
	px_x = 0;
	px_y = 0;
	print_2d(map->map);
	map_background(mlx, map, info);
	while (map->map[y])
	{
		while (map->map[y][x] != '\0')
		{
			if (map->map[y][x] == '0' || ft_strchr("NESW", map->map[y][x]))
			{
				while (k < map->sq)
				{
					while (i < map->sq)
					{
						mlx_put_pixel(info->img->map, px_x + i, px_y + k,
							get_rgba(0, 0, 0, 255));
						i++;
					}
					i = 0;
					k++;
				}
				k = 0;
			}
			else if (map->map[y][x] == '1')
			{
				while (k < map->sq)
				{
					while (i < map->sq)
					{
						mlx_put_pixel(info->img->map, px_x + i, px_y + k,
							get_rgba(200, 200, 200, 255));
						i++;
					}
					i = 0;
					k++;
				}
				k = 0;
			}
			x++;
			px_x += map->sq;
		}
		px_y += map->sq;
		px_x = 0;
		x = 0;
		y++;
	}
}

/* start by drawing three rays, one at 0, one at -30, one at + 30 */
void	draw_fov(mlx_t *mlx, t_map *map, t_info *info, int px_x, int px_y)
{
	int	i;
	int	ray_x;
	int	ray_y;

	i = 0;
	while (i < 30)
	{
		ray_x = px_x + round(i * cos(info->p_orient - M_PI / 6));
		ray_y = px_y + round(i * sin(info->p_orient - M_PI / 6));
		if (ray_x >= 0 && ray_y >= 0 && ray_x < info->img->plyr->width && ray_y < info->img->plyr->height)
			mlx_put_pixel(info->img->plyr, ray_x, ray_y,
				get_rgba(255, 255, 0, 255));
		ray_x = px_x + round(i * cos(info->p_orient + M_PI / 6));
		ray_y = px_y + round(i * sin(info->p_orient + M_PI / 6));
		if (ray_x >= 0 && ray_y >= 0 && ray_x < info->img->plyr->width && ray_y < info->img->plyr->height)
			mlx_put_pixel(info->img->plyr, ray_x, ray_y,
				get_rgba(255, 255, 0, 255));
		i++;
	}
}

void	draw_2d_player(mlx_t *mlx, t_map *map, t_info *info)
{
	int	px_x;
	int	px_y;
	int	i;
	int	k;

	px_x = info->p_x * map->sq - 5;
	px_y = info->p_y * map->sq - 5;
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
	draw_fov(mlx, map, info, px_x + 5, px_y + 5);
	
}

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
	draw_squares(mlx, map, info);
	draw_2d_player(mlx, map, info);
	mlx_image_to_window(mlx, info->img->plyr, 20, 20);
}
