/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_squares.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:20:46 by rboudwin          #+#    #+#             */
/*   Updated: 2024/10/21 15:22:53 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_2d_squares(t_map *map, t_info *info, t_sq *sq)
{
	sq->x = 0;
	sq->y = 0;
	sq->i = 0;
	sq->k = 0;
	sq->px_x = 0;
	sq->px_y = 0;
	print_2d(map->map);
	map_background(map, info);
}

void	draw_2d_wall(t_map *map, t_info *info, t_sq *sq)
{
	while (sq->k < map->sq)
	{
		while (sq->i < map->sq)
		{
			mlx_put_pixel(info->img->map, sq->px_x + sq->i, sq->px_y + sq->k,
				get_rgba(200, 200, 200, 255));
			sq->i++;
		}
		sq->i = 0;
		sq->k++;
	}
	sq->k = 0;
}

void	draw_2d_open_space(t_map *map, t_info *info, t_sq *sq)
{
	while (sq->k < map->sq)
	{
		while (sq->i < map->sq)
		{
			mlx_put_pixel(info->img->map, sq->px_x + sq->i, sq->px_y + sq->k,
				get_rgba(0, 0, 0, 255));
			sq->i++;
		}
		sq->i = 0;
		sq->k++;
	}
	sq->k = 0;
}

void	draw_squares(t_map *map, t_info *info)
{
	t_sq	sq;

	init_2d_squares(map, info, &sq);
	while (map->map[sq.y])
	{
		while (map->map[sq.y][sq.x] != '\0')
		{
			if (map->map[sq.y][sq.x] == '0'
				|| ft_strchr("NESW", map->map[sq.y][sq.x]))
				draw_2d_open_space(map, info, &sq);
			else if (map->map[sq.y][sq.x] == '1')
				draw_2d_wall(map, info, &sq);
			sq.x++;
			sq.px_x += map->sq;
		}
		sq.px_y += map->sq;
		sq.px_x = 0;
		sq.x = 0;
		sq.y++;
	}
}
