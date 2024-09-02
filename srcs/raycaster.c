/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 08:56:04 by rboudwin          #+#    #+#             */
/*   Updated: 2024/09/02 13:48:35 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// 'Encodes' four individual bytes into an int.
int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

char	detect_square(t_map *map, double x, double y)
{
	char	sq;
	int		rel_x;
	int		rel_y;
 
	rel_x = (int)floor(x);
	rel_y = (int)floor(y);

	sq = map->map[rel_y][rel_x];
	return (sq);
}

/*void	move_forward(t_map *info)
{
	if (detect_square(info->map, info->p_x + round(5 * sin(info->p_orient)), map->p_pos_y - round(cos(info->p_orient))) != '1')
	{
		map->p_pos_x += round(5 * sin(map->p_orient));
		map->p_pos_y -= round(5 * cos(map->p_orient));
	}
}

void	move_backward(t_map *map)
{
	if (detect_square(map, map->p_pos_x - round(5 * sin(map->p_orient)), map->p_pos_y + round(5 * cos(map->p_orient))) != '1')
	{
		map->p_pos_x -= round(5 * sin(map->p_orient));
		map->p_pos_y += round(5 * cos(map->p_orient));
	}
}

void	move_left(t_map *map)
{
	if (detect_square(map, map->p_pos_x + round(5 * sin(map->p_orient - 90 * DEG_2_RAD)), map->p_pos_y - round(5 * cos(map->p_orient - 90 * DEG_2_RAD))) != '1')
	{
		map->p_pos_x += round(5 * sin(map->p_orient - 90 * DEG_2_RAD));
		map->p_pos_y -= round(5 * cos(map->p_orient - 90 * DEG_2_RAD));
	}
}

void	move_right(t_map *map)
{
	if (detect_square(map, map->p_pos_x + round(5 * sin(map->p_orient + 90 * DEG_2_RAD)), map->p_pos_y - round(5 * cos(map->p_orient + 90 * DEG_2_RAD))) != '1')
	{
		map->p_pos_x += round(5 * sin(map->p_orient + 90 * DEG_2_RAD));
		map->p_pos_y -= round(5 * cos(map->p_orient + 90 * DEG_2_RAD));
	}
}

void	ft_movehook(void *param)
{
	t_info *info;

	info = (t_info *)param;
	if (mlx_is_key_down(info->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(info->mlx);
	if (mlx_is_key_down(info->mlx, MLX_KEY_W) || mlx_is_key_down(info->mlx, MLX_KEY_UP))
	{
		move_forward(info);
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_S) || mlx_is_key_down(info->mlx, MLX_KEY_DOWN))
	{
		move_backward(info);
	}

	if (mlx_is_key_down(info->mlx, MLX_KEY_A))
	{
		move_left(info);
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_D))
	{
		move_right(info);
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_LEFT))
	{
		info->p_orient -= 0.03490659; //2 degrees in radians
		if (info->p_orient <= 0)
			info->p_orient += 2 * M_PI;
	}
	if (mlx_is_key_down(info->mlx, MLX_KEY_RIGHT))
	{
		info->p_orient += 0.03490659; //2 degrees in radians
		if (map->p_orient >= 2 * M_PI)
			map->p_orient -= 2 * M_PI;
	}
	ray_caster(info->mlx, info->map, info->img);
}*/
void	ft_single_press_hook(mlx_key_data_t keydata, void *param)
{
	t_info	*info;

	info = (t_info *)param;
	if	(((keydata.key == MLX_KEY_M)
			&& keydata.action == MLX_PRESS))
	{
		if (info->map_visible)
		{
			info->map_visible = false;
			info->img->map->enabled = false;
			info->img->plyr->enabled = false;
			//info->img->fg->enabled = false;
			ft_printf("2D map turned off\n");
		}
		else
		{
			info->map_visible = true;
			info->img->map->enabled = true;
			info->img->plyr->enabled = true;
			//info->img->fg->enabled = true;
			ft_printf("2D map turned on\n");
		}
	}
}
void init_img(t_info *info)
{
	ft_printf("Inside init_img\n");
	ft_printf("width is %d and height is %d\n", info->s_width, info->s_height);
	ft_printf("mlx pointer is %p\n", info->mlx);
	info->img->bg = mlx_new_image(info->mlx, info->s_width, info->s_height);
	if (!info->img->bg)
		ft_putstr_fd("Image initialization error", 2);
	info->img->fg = mlx_new_image(info->mlx, info->s_width, info->s_height);
	info->img->world = mlx_new_image(info->mlx, info->s_width, info->s_height);
	info->img->map = mlx_new_image(info->mlx, info->map_width, info->map_height);
	info->img->plyr = mlx_new_image(info->mlx, info->map_width, info->map_height);
	ft_memset(info->img->bg->pixels, 180, info->img->bg->width
		* info->img->bg->height * BPP);
	mlx_image_to_window(info->mlx, info->img->bg, 0, 0);
	mlx_image_to_window(info->mlx, info->img->world, 0, 0);
	ft_memset(info->img->map->pixels, 255, info->img->map->width
		* info->img->map->height * BPP);
}

void init_plyr(t_info *info, t_map *map)
{
	int y;
	int x;
	int found;
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
			break;
	}
	if (!found)
		ft_putstr_fd("Error: No starting position found\n", 2);
	ft_printf("We have found the starting position at y: %d x: %d\n", y, x);
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
	 	ft_putstr_fd("Could not set player orientation\n", 2);
	printf("Our starting position is y: %f, x: %f, orientation is %f\n", info->p_y, info->p_x, info->p_orient); // this doesn't work because
	//ft_printf doesn't handle floats
	
}

void raycaster(mlx_t *mlx, t_map *map, t_images *img)
{
	
}

void draw_squares(mlx_t *mlx, t_map *map, t_info *info)
{
	int x;
	int y;
	int px_x;
	int px_y;
	x = 0;
	y = 0;
	int i = 0;
	int k = 0;
	px_x = 0;
	px_y = 0;
	ft_printf("inside draw_squares\n");
	print_2d(map->map);
	while (map->map[y])
	{
		//ft_printf("inside first while loop\n");
		while(map->map[y][x] != '\0')
		{
			//ft_printf("inside second while loop\n");
			//ft_printf("%c", map->map[y][x]);
			if (map->map[y][x] == '0' || ft_strchr("NESW", map->map[y][x]))
			{
			//	ft_printf("found a 0\n");
				while (k < map->sq)
				{
					while (i < map->sq)
					{
						mlx_put_pixel(info->img->map, px_x + i, px_y + k, get_rgba(0, 0, 0, 255));
						i++;
					}
					
					i = 0;
					k++;
				}
				k = 0;
				
			}
			else if (map->map[y][x] == '1')
			{
				//ft_printf("found a 0\n");
				while (k < map->sq)
				{
					while (i < map->sq)
					{
						mlx_put_pixel(info->img->map, px_x + i, px_y + k, get_rgba(200, 200, 200, 255));
						i++;
					}
					
					i = 0;
					k++;
				}
				k = 0;
				
			}
			x++;
			px_x += map->sq;
		}
		px_y += map->sq;
		
	px_x = 0;
	x = 0;
	y++;
	}
	
}

void draw_2d_player(mlx_t *mlx, t_map *map, t_info *info)
{
	
}

void draw_2d_map(mlx_t *mlx, t_map *map, t_info *info)
{	
	ft_printf("Drawing 2d map\n");
	mlx_image_to_window(info->mlx, info->img->map, info->map_width / 8, info->map_height / 8);
	mlx_image_to_window(info->mlx, info->img->plyr, info->map_width / 8, info->map_height / 8);
	
	map->x_len = 0;
	map->y_len = 0;
	ft_printf("map->map[0] is '%s'\n", map->map[0]);
	map->x_len = ft_strlen(map->map[0]);
	while (map->map[map->y_len])
	{
		map->y_len++;
	}
	ft_printf("Map is %d wide and %d tall\n", map->x_len, map->y_len);
	map->sq_w = info->map_width / map->x_len;
	map->sq_h = info->map_height / map->y_len;
	if (map->sq_w <= map->sq_h)
		map->sq = map->sq_w;
	else
		map->sq = map->sq_h;
	printf("Sq_w: %d\n Sq_h: %d\n sq: %d\n", map->sq_w, map->sq_h, map->sq);
	draw_squares(mlx, map, info);
	draw_2d_player(mlx, map, info);
}

void setup_mlx(t_map *map)
{
	t_info info;
	t_images img;
	
	info.map = map;
	info.img = &img;
	info.s_width = 1366;
	info.s_height = 768;
	info.map_size_factor = 0.75;
	info.map_width = info.s_width * info.map_size_factor;
	info.map_height = info.s_height * info.map_size_factor;
	info.map_visible = true;
	info.mlx = mlx_init(info.s_width, info.s_height, "cub3d", true);
	if (!info.mlx)
	{
		ft_putstr_fd("MLX initialization error\n", 2);
	}
	init_img(&info);
	init_plyr(&info, info.map);
	int i = 0;
	ft_printf("Loading map: \n");
	print_2d(map->map);
	draw_2d_map(info.mlx, info.map, &info);
	//raycaster(info.mlx, info.map, info.img); 
	mlx_key_hook(info.mlx, ft_single_press_hook, &info);
	mlx_loop(info.mlx);
	mlx_terminate(info.mlx);
}