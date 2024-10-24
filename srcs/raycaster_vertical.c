/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_vertical.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:37:24 by rboudwin          #+#    #+#             */
/*   Updated: 2024/10/24 08:20:39 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* moves verti_vec to the appropriate grid square edge */
void	get_to_vert_sq_edge(t_info *info)
{
	if (info->ray_orient >= M_PI_2 && info->ray_orient < 3 * M_PI_2)
		info->verti_vec[0] = floorf(info->ray_x) - 0.00001;
	else
		info->verti_vec[0] = ceilf(info->ray_x);
}

/* Finds the first vertical intersection and returns the vertical ray length */
double	find_first_vertical(t_info *info)
{
	double	delta_x;
	double	delta_y;
	double	len;

	get_to_vert_sq_edge(info);
	if (info->ray_orient >= M_PI_2 && info->ray_orient < 3 * M_PI_2)
		delta_x = -fabs(info->verti_vec[0] - info->ray_x);
	else
		delta_x = fabs(info->verti_vec[0] - info->ray_x);
	if (fabs(sin(info->ray_orient)) < EPSILON)
		delta_y = 0;
	else
	{
		if (info->ray_orient > M_PI)
			delta_y = -fabs(delta_x * tan(info->ray_orient));
		else
			delta_y = fabs(delta_x * tan(info->ray_orient));
	}
	info->verti_vec[1] = info->ray_y + delta_y;
	len = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
	return (len);
}

/* returns the ray length to the next vertical intersection */
double	find_next_vertical(t_info(*info), double len)
{
	double	delta_y;
	double	delta_x;

	if (info->ray_orient > M_PI_2 && info->ray_orient < M_PI_2 * 3)
		delta_x = -1.0;
	else
		delta_x = 1.0;
	if (fabs(sin(info->ray_orient)) < EPSILON)
		delta_y = 0;
	else
	{
		if (info->ray_orient > M_PI)
			delta_y = -fabs(delta_x * tan(info->ray_orient));
		else
			delta_y = fabs(delta_x * tan(info->ray_orient));
	}
	info->verti_vec[0] = info->verti_vec[0] + delta_x;
	info->verti_vec[1] = info->verti_vec[1] + delta_y;
	len += sqrt(pow(delta_x, 2) + pow(delta_y, 2));
	return (len);
}
