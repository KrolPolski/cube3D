/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:28:43 by rboudwin          #+#    #+#             */
/*   Updated: 2024/10/18 12:34:34 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_img(t_info *info)
{
	// need to add error checking on these
	// also need to free all textures if we are going to fail
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
	else
	{
		//ft_putstr_fd("We must have suceeded in loading textures\n", 1);
		//printf("txt_no: %p txt_ea: %p txt_so: %p txt_we: %p",
		//	info->img->txt_no, info->img->txt_ea, info->img->txt_so,
		//	info->img->txt_we);
	}
	info->img->no = mlx_texture_to_image(info->mlx, info->img->txt_no);
	info->img->ea = mlx_texture_to_image(info->mlx, info->img->txt_ea);
	info->img->so = mlx_texture_to_image(info->mlx, info->img->txt_so);
	info->img->we = mlx_texture_to_image(info->mlx, info->img->txt_we);
	//add safeguards for large textures
	if (info->img->no->height > 256 || info->img->no->width > 256)
		mlx_resize_image(info->img->no, 256, 256);
	if (info->img->ea->height > 256 || info->img->ea->width > 256)
		mlx_resize_image(info->img->ea, 256, 256);
	if (info->img->so->height > 256 || info->img->so->width > 256)
		mlx_resize_image(info->img->so, 256, 256);
	if (info->img->we->height > 256 || info->img->we->width > 256)
		mlx_resize_image(info->img->we, 256, 256);
	info->img->bg = mlx_new_image(info->mlx, info->s_width, info->s_height);
	info->img->fg = mlx_new_image(info->mlx, info->s_width, info->s_height);
	info->img->world = mlx_new_image(info->mlx, info->s_width, info->s_height);
	info->img->map = mlx_new_image(info->mlx, info->map_width,
			info->map_height);
	info->img->plyr = mlx_new_image(info->mlx, info->map_width,
			info->map_height);
	if (!info->img->bg || !info->img->world || !info->img->map || !info->img->plyr)
	{
		ft_putstr_fd("Image initialization error", 2);
		exit(1);
	}
	ft_memset(info->img->bg->pixels, 180, info->img->bg->width
		* info->img->bg->height * BPP);
	mlx_image_to_window(info->mlx, info->img->bg, 0, 0);
	mlx_image_to_window(info->mlx, info->img->world, 0, 0);
	ft_memset(info->img->map->pixels, 255, info->img->map->width
		* info->img->map->height * BPP);
}

void	init_plyr(t_info *info, t_map *map)
{
	int	y;
	int	x;
	int	found;

	found = 0;
	y = 0;
	x = 0;
	while (map->map[y])
	{
		while (map->map[y][x])
		{
			if (ft_strchr("NESW", map->map[y][x]))
			{
				found = 1;
				break ;
			}
			x++;
		}
		if (!found)
		{
			x = 0;
			y++;
		}
		else
			break ;
	}
	if (!found)
	{
		ft_putstr_fd("Error: No starting position found\n", 2);
		exit(1);
	}
	info->p_x = x + 0.5;
	info->p_y = y + 0.5;
	info->p_orient = 42;
	if (map->map[y][x] == 'N')
		info->p_orient = M_PI + M_PI_2;
	else if (map->map[y][x] == 'E')
		info->p_orient = 0;
	else if (map->map[y][x] == 'S')
		info->p_orient = M_PI_2;
	else if (map->map[y][x] == 'W')
		info->p_orient = M_PI;
	else
	{
		ft_putstr_fd("Could not set player orientation\n", 2);
		exit(1);
	}
	//printf("Our starting position is y: %f, x: %f, orientation is %f\n",
	//	info->p_y, info->p_x, info->p_orient);
}