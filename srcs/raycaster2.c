/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:46:43 by rboudwin          #+#    #+#             */
/*   Updated: 2024/10/17 15:46:46 by rboudwin         ###   ########.fr       */
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

double	find_first_vertical(mlx_t *mlx, t_map *map, t_info *info)
{
	double	delta_x;
	double	delta_y;
	double	previous_position;
	double	len;

	previous_position = info->ray_x;
	if (info->ray_orient >= M_PI_2 && info->ray_orient < 3 * M_PI_2)
		info->verti_vec[0] = floorf(info->ray_x) - 0.00001;
	else
		info->verti_vec[0] = ceilf(info->ray_x);
	if (info->ray_orient >= M_PI_2 && info->ray_orient < 3 * M_PI_2)
	{
		delta_x = -fabs(info->verti_vec[0] - info->ray_x);
	}
	else
	{
		delta_x = fabs(info->verti_vec[0] - info->ray_x);
	}
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

double	find_next_vertical(mlx_t *mlx, t_map *map, t_info(*info), double len)
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

double	find_first_horizontal(mlx_t *mlx, t_map *map, t_info *info)
{
	double	delta_x;
	double	delta_y;
	double	previous_position;
	double	len;

	previous_position = info->ray_y;
	if (info->ray_orient > M_PI)
		info->horiz_vec[1] = floorf(info->ray_y) - 0.00001;
	else
		info->horiz_vec[1] = ceilf(info->ray_y);
	if (info->ray_orient > M_PI)
	{
		delta_y = -fabs(info->horiz_vec[1] - info->ray_y);
	}
	else
	{
		delta_y = fabs(info->horiz_vec[1] - info->ray_y);
	}
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

double	find_next_horizontal(mlx_t *mlx, t_map *map, t_info *info, double len)
{
	double	delta_y;
	double	delta_x;
	double	x_candidate;
	double	y_candidate;

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
	//add error correction
	return (NULL);
}

unsigned int	find_x_percent(double ray_len, t_info *info, t_images *img,
	enum e_intersect inter)
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

void	cast_wall(double ray_len, int i, t_info *info, t_images *img,
	enum e_intersect inter)
{
	int				top_pixel;
	int				pixels;
	int				color;
	float			angle;
	unsigned int	column_height;
	int				proj_plane_dist;
	unsigned int	x_percent;
	mlx_image_t		*texture_img;
	unsigned int	texel;
	unsigned int	pixels_per_texel;
	unsigned int	leftovers;
	int				y;
	int				texel_y_int;
	double			texel_step;
	double			texel_y;

	y = 0;
	proj_plane_dist = (info->s_width / 2) / tan(M_PI / 6);
	texture_img = get_wall_texture(img, info->ray_orient, inter);
	x_percent = find_x_percent(ray_len, info, img, inter);
	if (ray_len > info->rend_dist)
		return ;
	top_pixel = 0;
	pixels = 0;
	column_height = (info->s_height / (ray_len
				* cos(info->ray_orient - info->p_orient)));
	top_pixel = info->s_height / 2 - column_height / 2;
	texel = texture_img->width * x_percent / 100;
	pixels_per_texel = round((double)column_height
				/ (double)texture_img->height);
	color = mlx_get_pixel(texture_img, texel, 0);
	leftovers = column_height % pixels_per_texel;
	texel_step = (double)texture_img->height / (double)column_height;
	texel_y = 0;
	if (top_pixel < 0)
	{
		texel_y = -(top_pixel * texel_step);
		top_pixel = 0;
	}
	while (pixels < column_height - 1)
	{
		if (top_pixel + pixels > info->s_height - 1 || top_pixel + pixels < 0
			|| i > info->s_width || i < 0)
		{
			break ;
		}
		mlx_put_pixel(img->world, i, top_pixel + pixels, color);
		pixels++;
		texel_y_int = (int)texel_y;
		color = mlx_get_pixel(texture_img, texel, texel_y_int);
		texel_y += texel_step;
	}
}

void	raycaster(mlx_t *mlx, t_map *map, t_images *img, t_info *info)
{
	double				ray_len;
	double				ray_x_len;
	double				ray_y_len;
	double				horiz_len;
	double				verti_len;
	double				len_parking;
	char				ret;
	int					i;
	enum e_intersect	inter;

	info->ray_x = info->p_x;
	info->ray_y = info->p_y;
	info->ray_orient = info->p_orient - (M_PI / 6);
	ft_memset(img->world->pixels, 0, img->world->height * img->world->width * BPP);
	//mlx_delete_image(mlx, img->world);
	//img->world = mlx_new_image(mlx, info->s_width, info->s_height);
	//mlx_image_to_window(mlx, img->world, 0, 0);
	i = 0;
	while (i < info->s_width)
	{
		check_radian_overflow(info);
		ray_len = 0;
		info->ray_x = info->p_x;
		info->ray_y = info->p_y;
		horiz_len = find_first_horizontal(mlx, map, info);
		verti_len = find_first_vertical(mlx, map, info);
		if (horiz_len < verti_len)
			ray_len = horiz_len;
		else
			ray_len = verti_len;
		while (detect_square(map, info->horiz_vec[0],
				info->horiz_vec[1]) != '1')
		{
			horiz_len = find_next_horizontal(mlx, map, info, horiz_len);
		}
		while (detect_square(map, info->verti_vec[0],
				info->verti_vec[1]) != '1')
		{
			verti_len = find_next_vertical(mlx, map, info, verti_len);
		}
		if (horiz_len < verti_len)
		{
			ray_len = horiz_len;
			inter = horizontal;
		}
		else
		{
			ray_len = verti_len;
			inter = vertical;
		}
		cast_wall(ray_len, i, info, img, inter);
		i++;
		info->ray_orient += (M_PI / 3.0) * (1.0 / (double)info->s_width);
	}
}
