/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:46:43 by rboudwin          #+#    #+#             */
/*   Updated: 2024/10/21 16:49:12 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
 * In MLX42 Colors are as follows:
 * 0000 0000 A (1st byte) -> uint8_t because it's 8 bits
 * 0000 0000 R (2nd byte)
 * 0000 0000 G (3rd byte)
 * 0000 0000 B (4th byte)
 */
int32_t	mlx_get_pixel(mlx_image_t *image, uint32_t x, uint32_t y)
{
	uint8_t	*pixelstart;

	if (x > image->width || y > image->height)
		return (0xFF000000);
	pixelstart = image->pixels + (y * image->width + x) * BPP;
	return (get_rgba(*(pixelstart), *(pixelstart + 1),
			*(pixelstart + 2), *(pixelstart + 3)));
}

void	check_radian_overflow(t_info *info)
{
	if (info->ray_orient > 2 * M_PI)
		info->ray_orient -= 2 * M_PI;
	else if (info->ray_orient < 0)
		info->ray_orient += 2 * M_PI;
	else
		return ;
}

double	determine_ray_len(t_info *info, enum e_intersect *inter, t_map *map)
{
	double	horiz_len;
	double	verti_len;
	double	ray_len;

	horiz_len = find_first_horizontal(info);
	verti_len = find_first_vertical(info);
	while (detect_square(map, info->horiz_vec[0],
			info->horiz_vec[1]) != '1')
		horiz_len = find_next_horizontal(info, horiz_len);
	while (detect_square(map, info->verti_vec[0],
			info->verti_vec[1]) != '1')
		verti_len = find_next_vertical(info, verti_len);
	if (horiz_len < verti_len)
	{
		ray_len = horiz_len;
		*inter = horizontal;
	}
	else
	{
		ray_len = verti_len;
		*inter = vertical;
	}
	return (ray_len);
}

void	raycaster(t_map *map, t_images *img, t_info *info)
{
	double				ray_len;
	unsigned int		i;
	enum e_intersect	inter;

	info->ray_orient = info->p_orient - (M_PI / 6);
	ft_memset(img->world->pixels, 0, img->world->height * img->world->width
		* BPP);
	i = 0;
	while (i < info->s_width)
	{
		check_radian_overflow(info);
		ray_len = 0;
		info->ray_x = info->p_x;
		info->ray_y = info->p_y;
		ray_len = determine_ray_len(info, &inter, map);
		cast_wall(ray_len, i, info, inter);
		i++;
		info->ray_orient += (M_PI / 3.0) * (1.0 / (double)info->s_width);
	}
}
