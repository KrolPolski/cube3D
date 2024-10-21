/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_horiz.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:39:49 by rboudwin          #+#    #+#             */
/*   Updated: 2024/10/21 17:28:39 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Moves horiz_vec to the appropriate grid square border */
void	get_to_horiz_sq_edge(t_info *info)
{
	if (info->ray_orient > M_PI)
		info->horiz_vec[1] = floorf(info->ray_y) - 0.00001;
	else
		info->horiz_vec[1] = ceilf(info->ray_y);
}

/* Detects first horizontal intersection and returns the
horizontal ray length */
double	find_first_horizontal(t_info *info)
{
	double	delta_x;
	double	delta_y;
	double	previous_position;
	double	len;

	previous_position = info->ray_y;
	get_to_horiz_sq_edge(info);
	if (info->ray_orient > M_PI)
		delta_y = -fabs(info->horiz_vec[1] - info->ray_y);
	else
		delta_y = fabs(info->horiz_vec[1] - info->ray_y);
	if (fabs(cos(info->ray_orient)) < EPSILON)
		delta_x = 0;
	else
	{
		if (info->ray_orient < M_PI_2 || info->ray_orient > M_PI * 1.5)
			delta_x = fabs(delta_y / tan(info->ray_orient));
		else
			delta_x = -fabs(delta_y / tan(info->ray_orient));
	}
	info->horiz_vec[0] = info->ray_x + delta_x;
	len = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
	return (len);
}

/* determines ray length to the next horizontal intersection */
double	find_next_horizontal(t_info *info, double len)
{
	double	delta_y;
	double	delta_x;

	if (info->ray_orient > M_PI)
		delta_y = -1.0;
	else
		delta_y = 1.0;
	if (fabs(cos(info->ray_orient)) < EPSILON)
		delta_x = 0;
	else
	{
		if (info->ray_orient < M_PI_2 || info->ray_orient > M_PI * 1.5)
			delta_x = fabs(delta_y / tan(info->ray_orient));
		else
			delta_x = -fabs(delta_y / tan(info->ray_orient));
	}
	info->horiz_vec[0] = info->horiz_vec[0] + delta_x;
	info->horiz_vec[1] = info->horiz_vec[1] + delta_y;
	len += sqrt(pow(delta_x, 2) + pow(delta_y, 2));
	return (len);
}
