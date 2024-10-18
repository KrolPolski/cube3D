/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_hooks2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:30:49 by rboudwin          #+#    #+#             */
/*   Updated: 2024/10/18 13:31:17 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_forward(t_info *info)
{
	if (detect_square(info->map, info->p_x + (cos(info->p_orient)) / 5,
			info->p_y + (sin(info->p_orient)) / 5) != '1')
	{
		info->p_x += (cos(info->p_orient)) / 20;
		info->p_y += (sin(info->p_orient)) / 20;
	}
}

void	move_backward(t_info *info)
{
	if (detect_square(info->map, info->p_x - cos(info->p_orient) / 5,
			info->p_y - sin(info->p_orient) / 5) != '1')
	{
		info->p_x -= (cos(info->p_orient)) / 20;
		info->p_y -= (sin(info->p_orient)) / 20;
	}
}

void	move_left(t_info *info)
{
	if (detect_square(info->map, info->p_x + cos(info->p_orient - M_PI_2) / 5,
			info->p_y + sin(info->p_orient - M_PI_2) / 5) != '1')
	{
		info->p_x += cos(info->p_orient - M_PI_2) / 20;
		info->p_y += sin(info->p_orient - M_PI_2) / 20;
	}
}

void	move_right(t_info *info)
{
	if (detect_square(info->map, info->p_x + cos(info->p_orient + M_PI_2) / 5,
			info->p_y + sin(info->p_orient + M_PI_2) / 5) != '1')
	{
		info->p_x += cos(info->p_orient + M_PI_2) / 20;
		info->p_y += sin(info->p_orient + M_PI_2) / 20;
	}
}
