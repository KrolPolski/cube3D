/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:30:44 by rboudwin          #+#    #+#             */
/*   Updated: 2024/10/18 13:37:46 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_rotation(t_info *info)
{
	if (mlx_is_key_down(info->mlx, MLX_KEY_LEFT))
	{
		info->p_orient -= 0.03490659;
		if (info->p_orient <= 0)
			info->p_orient += 2 * M_PI;
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_RIGHT))
	{
		info->p_orient += 0.03490659;
		if (info->p_orient >= 2 * M_PI)
			info->p_orient -= 2 * M_PI;
	}
}

void	ft_movehook(void *param)
{
	t_info	*info;

	info = (t_info *)param;
	if (mlx_is_key_down(info->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(info->mlx);
	if (mlx_is_key_down(info->mlx, MLX_KEY_W)
		|| mlx_is_key_down(info->mlx, MLX_KEY_UP))
		move_forward(info);
	if (mlx_is_key_down(info->mlx, MLX_KEY_S)
		|| mlx_is_key_down(info->mlx, MLX_KEY_DOWN))
		move_backward(info);
	if (mlx_is_key_down(info->mlx, MLX_KEY_A))
		move_left(info);
	if (mlx_is_key_down(info->mlx, MLX_KEY_D))
		move_right(info);
	check_rotation(info);
	raycaster(info->mlx, info->map, info->img, info);
	if (info->img->plyr->enabled)
		draw_2d_player(info->mlx, info->map, info);
}

void	ft_single_press_hook(mlx_key_data_t keydata, void *param)
{
	t_info	*info;

	info = (t_info *)param;
	if (keydata.key == MLX_KEY_M
		&& keydata.action == MLX_PRESS)
	{
		if (info->map_visible)
		{
			info->map_visible = false;
			info->img->map->enabled = false;
			info->img->plyr->enabled = false;
			ft_printf("2D map turned off\n");
		}
		else
		{
			info->map_visible = true;
			info->img->map->enabled = true;
			info->img->plyr->enabled = true;
			ft_printf("2D map turned on\n");
		}
	}
}
