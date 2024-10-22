/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:28:43 by rboudwin          #+#    #+#             */
/*   Updated: 2024/10/21 17:21:11 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Safeguards against textures that are unreasonably large */
void	check_texture_size(t_info *info)
{
	if (info->img->no->height > 256 || info->img->no->width > 256)
		mlx_resize_image(info->img->no, 256, 256);
	if (info->img->ea->height > 256 || info->img->ea->width > 256)
		mlx_resize_image(info->img->ea, 256, 256);
	if (info->img->so->height > 256 || info->img->so->width > 256)
		mlx_resize_image(info->img->so, 256, 256);
	if (info->img->we->height > 256 || info->img->we->width > 256)
		mlx_resize_image(info->img->we, 256, 256);
}

/* Loads textures from files and converts them to images */
void	load_wall_textures(t_info *info)
{
	info->img->txt_no = mlx_load_png(info->map->no);
	info->img->txt_ea = mlx_load_png(info->map->ea);
	info->img->txt_so = mlx_load_png(info->map->so);
	info->img->txt_we = mlx_load_png(info->map->we);
	if (!info->img->txt_no || !info->img->txt_ea
		|| !info->img->txt_so || !info->img->txt_no)
	{
		ft_putstr_fd("Unable to load texture\n", 2);
		exit(1);
	}
	info->img->no = mlx_texture_to_image(info->mlx, info->img->txt_no);
	info->img->ea = mlx_texture_to_image(info->mlx, info->img->txt_ea);
	info->img->so = mlx_texture_to_image(info->mlx, info->img->txt_so);
	info->img->we = mlx_texture_to_image(info->mlx, info->img->txt_we);
}

/* Initializes all the images we will need */
void	init_img(t_info *info)
{
	load_wall_textures(info);
	check_texture_size(info);
	info->img->bg = mlx_new_image(info->mlx, info->s_width, info->s_height);
	info->img->world = mlx_new_image(info->mlx, info->s_width, info->s_height);
	info->img->map = mlx_new_image(info->mlx, info->map_width,
			info->map_height);
	info->img->plyr = mlx_new_image(info->mlx, info->map_width,
			info->map_height);
	if (!info->img->bg || !info->img->world || !info->img->map
		|| !info->img->plyr)
	{
		ft_putstr_fd("Image initialization error", 2);
		exit(1);
	}
	mlx_image_to_window(info->mlx, info->img->bg, 0, 0);
	mlx_image_to_window(info->mlx, info->img->world, 0, 0);
}
