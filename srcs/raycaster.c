/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 08:56:04 by rboudwin          #+#    #+#             */
/*   Updated: 2024/08/28 09:09:55 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void setup_mlx(t_map *map)
{
	t_info info;

	info.map = map;
	info.s_width = 1366;
	info.s_height = 768;
	info.mlx = mlx_init(info.s_width, info.s_height, "cub3d", true);
	mlx_loop(info.mlx);
	mlx_terminate(info.mlx);
}