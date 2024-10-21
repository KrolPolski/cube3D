/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:46:43 by rboudwin          #+#    #+#             */
/*   Updated: 2024/10/21 16:42:35 by rboudwin         ###   ########.fr       */
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

mlx_image_t	*get_wall_texture(t_images *img, double ray_orient,
	enum e_intersect inter)
{
	if (inter == horizontal)
	{
		if (ray_orient >= M_PI)
			return (img->so);
		else
			return (img->no);
	}
	else if (inter == vertical)
	{
		if (ray_orient >= M_PI_2 && ray_orient < (M_PI * 1.5))
			return (img->ea);
		else
			return (img->we);
	}
	return (NULL);
}

unsigned int	find_x_percent(t_info *info, enum e_intersect inter)
{
	double			x_fraction;
	double			zero;
	double			percent;
	unsigned int	int_percent;

	zero = 0;
	if (inter == vertical)
	{
		x_fraction = modf(info->verti_vec[1], &zero);
	}
	else
	{
		x_fraction = modf(info->horiz_vec[0], &zero);
	}
	percent = x_fraction * 100;
	int_percent = (unsigned int)floor(percent);
	return (int_percent);
}

void	draw_wall(t_cw *cw, t_info *info, unsigned int i)
{
	if (cw->column_height > info->s_height)
		cw->column_height = info->s_height;
	while (cw->pixels < cw->column_height - 1)
	{
		if (cw->top_pixel + cw->pixels > info->s_height - 1 || cw->top_pixel
			+ cw->pixels < 0 || i > info->s_width || i < 0)
		{
			break ;
		}
		mlx_put_pixel(info->img->world, i, cw->top_pixel + cw->pixels,
			cw->color);
		cw->pixels++;
		cw->texel_y_int = (int)cw->texel_y;
		cw->color = mlx_get_pixel(cw->texture_img, cw->texel, cw->texel_y_int);
		cw->texel_y += cw->texel_step;
	}
}

void	init_cast_wall(t_cw *cw, t_info *info, double ray_len,
	enum e_intersect inter)
{
	cw->y = 0;
	cw->texture_img = get_wall_texture(info->img, info->ray_orient, inter);
	cw->x_percent = find_x_percent(info, inter);
	cw->top_pixel = 0;
	cw->pixels = 0;
	cw->angle_diff = cos(info->ray_orient - info->p_orient);
	if (fabs(cw->angle_diff) > EPSILON)
		cw->column_height = (info->s_height / (ray_len
					* cw->angle_diff));
	else
		cw->column_height = info->s_height / ray_len;
	cw->top_pixel = info->s_height / 2 - cw->column_height / 2;
	cw->texel = cw->texture_img->width * cw->x_percent / 100;
}

void	cast_wall(double ray_len, unsigned int i, t_info *info,
	enum e_intersect inter)
{
	t_cw	cw;

	if (ray_len > info->rend_dist)
		return ;
	init_cast_wall(&cw, info, ray_len, inter);
	if (cw.texture_img->height != 0)
		cw.pixels_per_texel = round((double)cw.column_height
				/ (double)cw.texture_img->height);
	else
		return ;
	cw.color = mlx_get_pixel(cw.texture_img, cw.texel, 0);
	if (cw.column_height > EPSILON)
		cw.texel_step = (double)cw.texture_img->height
			/ (double)cw.column_height;
	else
		return ;
	cw.texel_y = 0;
	if (cw.top_pixel < 0)
	{
		cw.texel_y = -(cw.top_pixel * cw.texel_step);
		cw.top_pixel = 0;
	}
	draw_wall(&cw, info, i);
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
