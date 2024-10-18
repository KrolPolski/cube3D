/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 12:25:30 by rboudwin          #+#    #+#             */
/*   Updated: 2024/10/18 12:27:15 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	cleanup_images(mlx_t *mlx, t_images *img)
{
	mlx_delete_image(mlx, img->no);
	mlx_delete_image(mlx, img->ea);
	mlx_delete_image(mlx, img->so);
	mlx_delete_image(mlx, img->we);
	mlx_delete_texture(img->txt_no);
	mlx_delete_texture(img->txt_ea);
	mlx_delete_texture(img->txt_so);
	mlx_delete_texture(img->txt_we);
} 

void handle_resize(int width, int height, void *param)
{
    t_info	*info;

	info = (t_info *)param;
    info->s_width = width;
    info->s_height = height;
	info->map_width = width * info->map_size_factor;
    info->map_height = height * info->map_size_factor;
    mlx_resize_image(info->img->background, width, height);
    mlx_resize_image(info->img->world, width, height);
    mlx_resize_image(info->img->map, info->map_width, info->map_height);
    mlx_resize_image(info->img->plyr, info->map_width, info->map_height);
    draw_2d_map(info->mlx, info->map, info);
}

void	setup_mlx(t_map *map)
{
	t_info		info;
	t_images	img;
	int			i;

	info.map = map;
	info.img = &img;
	info.s_width = 1366;
	info.s_height = 768;
	info.map_size_factor = 0.3;
	info.rend_dist = 25;
	info.map_width = info.s_width * info.map_size_factor;
	info.map_height = info.s_height * info.map_size_factor;
	info.map_visible = true;
	info.mlx = mlx_init(info.s_width, info.s_height, "cub3d", true);
	if (!info.mlx)
	{
		ft_putstr_fd("MLX initialization error\n", 2);
		exit(1);
	}
	mlx_resize_hook(info.mlx, handle_resize, &info);
	init_img(&info);
	init_plyr(&info, info.map);
	floor_and_ceiling(info.mlx, info.img, &info, info.map);
	mlx_image_to_window(info.mlx, info.img->world, 0, 0);
	draw_2d_map(info.mlx, info.map, &info);
	raycaster(info.mlx, info.map, info.img, &info);
	mlx_key_hook(info.mlx, ft_single_press_hook, &info);
	mlx_loop_hook(info.mlx, ft_movehook, &info);
	mlx_loop(info.mlx);
	cleanup_images(info.mlx, info.img);
	mlx_terminate(info.mlx);
}