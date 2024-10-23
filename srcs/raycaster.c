/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 08:56:04 by rboudwin          #+#    #+#             */
/*   Updated: 2024/10/23 11:21:27 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>

/* 'Encodes' four individual bytes of RGB color and transparency information
into an 32 bit int.*/
int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/* Detects whether a given square is a wall or not and returns the map char 
at a given x and y */
char	detect_square(t_map *map, double x, double y)
{
	char	sq;
	int		rel_x;
	int		rel_y;

	rel_x = (int)floor(x);
	rel_y = (int)floor(y);
	if (rel_x < map->x_len && rel_y < map->y_len
		&& rel_x >= 0 && rel_y >= 0)
	{
		sq = map->map[rel_y][rel_x];
		if (sq == ' ')
			return ('1');
		else
			return (sq);
	}
	else
	{
		return ('1');
	}
}

/* Sets floor and ceiling colors on the background image */
void	floor_and_ceiling(t_images *img, t_info *info, t_map *map)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < info->s_height)
	{
		j = 0;
		while (j < info->s_width)
		{
			if (i < info->s_height / 2)
				mlx_put_pixel(img->bg, j, i,
					get_rgba(map->c[0], map->c[1], map->c[2], 255));
			else
				mlx_put_pixel(img->bg, j, i,
					get_rgba(map->f[0], map->f[1], map->f[2], 255));
			j++;
		}
		i++;
	}
}
