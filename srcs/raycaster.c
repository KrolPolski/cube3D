/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 08:56:04 by rboudwin          #+#    #+#             */
/*   Updated: 2024/08/28 10:22:13 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// 'Encodes' four individual bytes into an int.
int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

char	detect_square(t_map *map, double x, double y)
{
	char	sq;
	int		rel_x;
	int		rel_y;
 
	rel_x = (int)floor(x);
	rel_y = (int)floor(y);

	sq = map->map[rel_y][rel_x];
	return (sq);
}

/*void	move_forward(t_map *info)
{
	if (detect_square(info->map, info->p_x + round(5 * sin(info->p_orient)), map->p_pos_y - round(cos(info->p_orient))) != '1')
	{
		map->p_pos_x += round(5 * sin(map->p_orient));
		map->p_pos_y -= round(5 * cos(map->p_orient));
	}
}

void	move_backward(t_map *map)
{
	if (detect_square(map, map->p_pos_x - round(5 * sin(map->p_orient)), map->p_pos_y + round(5 * cos(map->p_orient))) != '1')
	{
		map->p_pos_x -= round(5 * sin(map->p_orient));
		map->p_pos_y += round(5 * cos(map->p_orient));
	}
}

void	move_left(t_map *map)
{
	if (detect_square(map, map->p_pos_x + round(5 * sin(map->p_orient - 90 * DEG_2_RAD)), map->p_pos_y - round(5 * cos(map->p_orient - 90 * DEG_2_RAD))) != '1')
	{
		map->p_pos_x += round(5 * sin(map->p_orient - 90 * DEG_2_RAD));
		map->p_pos_y -= round(5 * cos(map->p_orient - 90 * DEG_2_RAD));
	}
}

void	move_right(t_map *map)
{
	if (detect_square(map, map->p_pos_x + round(5 * sin(map->p_orient + 90 * DEG_2_RAD)), map->p_pos_y - round(5 * cos(map->p_orient + 90 * DEG_2_RAD))) != '1')
	{
		map->p_pos_x += round(5 * sin(map->p_orient + 90 * DEG_2_RAD));
		map->p_pos_y -= round(5 * cos(map->p_orient + 90 * DEG_2_RAD));
	}
}

void	ft_movehook(void *param)
{
	t_info *info;

	info = (t_info *)param;
	if (mlx_is_key_down(info->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(info->mlx);
	if (mlx_is_key_down(info->mlx, MLX_KEY_W) || mlx_is_key_down(info->mlx, MLX_KEY_UP))
	{
		move_forward(info);
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_S) || mlx_is_key_down(info->mlx, MLX_KEY_DOWN))
	{
		move_backward(info);
	}

	if (mlx_is_key_down(info->mlx, MLX_KEY_A))
	{
		move_left(info);
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_D))
	{
		move_right(info);
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_LEFT))
	{
		info->p_orient -= 0.03490659; //2 degrees in radians
		if (info->p_orient <= 0)
			info->p_orient += 2 * M_PI;
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_RIGHT))
	{
		info->p_orient += 0.03490659; //2 degrees in radians
		if (map->p_orient >= 2 * M_PI)
			map->p_orient -= 2 * M_PI;
	}
	ray_caster(info->mlx, info->map, info->img);
}*/

void init_img(t_info *info)
{
	info->img->bg = mlx_new_image(info->mlx, info->s_width, info->s_height);
	info->img->fg = mlx_new_image(info->mlx, info->s_width, info->s_height);
	ft_memset(info->img->bg->pixels, 255, info->img->bg->width
		* info->img->bg->height * BPP);
	mlx_image_to_window(info->mlx, info->img->bg, 0, 0);
}
void setup_mlx(t_map *map)
{
	t_info info;

	info.map = map;
	info.s_width = 1366;
	info.s_height = 768;
	info.mlx = mlx_init(info.s_width, info.s_height, "cub3d", true);
	init_img(&info);
	mlx_loop(info.mlx);
	mlx_terminate(info.mlx);
}