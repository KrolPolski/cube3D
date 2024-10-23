/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboudwin <rboudwin@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 12:05:40 by tparratt          #+#    #+#             */
/*   Updated: 2024/10/23 11:42:21 by rboudwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define BPP 4
# define EPSILON 1e-5
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/include/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_map
{
	char	**map;
	int		start_i;
	int		start_j;
	char	**copy;
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	char	*floor;
	char	*ceiling;
	int		*f;
	int		*c;
	int		x_len;
	int		y_len;
	int		sq_w;
	int		sq_h;
	int		sq;
}			t_map;

typedef struct s_images
{
	mlx_texture_t	*txt_no;
	mlx_texture_t	*txt_so;
	mlx_texture_t	*txt_ea;
	mlx_texture_t	*txt_we;
	mlx_image_t		*no;
	mlx_image_t		*ea;
	mlx_image_t		*so;
	mlx_image_t		*we;
	mlx_image_t		*world;
	mlx_image_t		*bg;
	mlx_image_t		*plyr;
	mlx_image_t		*map;
}					t_images;

enum				e_dir
{
	north,
	east,
	south,
	west,
	error,
};

enum e_intersect
{
	horizontal,
	vertical
};

typedef struct s_info
{
	unsigned int	s_width;
	unsigned int	s_height;
	mlx_t			*mlx;
	t_map			*map;
	t_images		*img;
	double			p_x;
	double			p_y;
	double			p_orient;
	double			ray_x;
	double			ray_y;
	double			ray_orient;
	double			horiz_vec[2];
	double			verti_vec[2];
	double			rend_dist;
	bool			map_visible;
	double			map_size_factor;
	int				map_width;
	int				map_height;
}	t_info;

typedef struct s_2d_sq
{
	int	x;
	int	y;
	int	px_x;
	int	px_y;
	int	i;
	int	k;
}	t_sq;

typedef struct s_cast_wall
{
	int				top_pixel;
	unsigned int	pixels;
	int				color;
	unsigned int	column_height;
	unsigned int	x_percent;
	mlx_image_t		*texture_img;
	unsigned int	texel;
	unsigned int	pixels_per_texel;
	int				y;
	int				texel_y_int;
	double			texel_step;
	double			texel_y;
	double			angle_diff;
}	t_cw;

int		all_whitespace(char *line);
void	cast_wall(double ray_len, unsigned int i, t_info *info,
			enum e_intersect inter);
void	check_chars(t_map *map);
void	check_walls(t_map *map);
void	copy_map(t_map *map);
void	draw_2d_map(mlx_t *mlx, t_map *map, t_info *info);
void	draw_2d_player(t_map *map, t_info *info);
void	draw_squares(t_map *map, t_info *info);
char	detect_square(t_map *map, double x, double y);
int		file_to_map(t_map *map, int i, char *line);
double	find_first_horizontal(t_info *info);
double	find_first_vertical(t_info *info);
double	find_next_horizontal(t_info *info, double len);
double	find_next_vertical(t_info(*info), double len);
void	floor_and_ceiling(t_images *img, t_info *info, t_map *map);
void	free_2d(char **arr);
void	free_map(t_map *map);
void	ft_single_press_hook(mlx_key_data_t keydata, void *param);
void	ft_movehook(void *param);
char	*ft_strchr_rev(const char *s, int c);
char	*ft_strdup_mod(const char *s1);
int		get_rgba(int r, int g, int b, int a);
int		identify_line(char *line);
void	init_img(t_info *info);
void	init_plyr(t_info *info, t_map *map);
int		invalid_file_extension(char *arg, char *lower, char *upper);
size_t	len_2d(char **arr);
void	map_background(t_map *map, t_info *info);
int32_t	mlx_get_pixel(mlx_image_t *image, uint32_t x, uint32_t y);
void	move_backward(t_info *info);
void	move_forward(t_info *info);
void	move_left(t_info *info);
void	move_right(t_info *info);
void	parse(char **argv, t_map *map);
void	print_2d(char **arr);
void	print_error(char *str, t_map *map);
void	raycaster(t_map *map, t_images *img, t_info *info);
int		*set_color(char *str, char **arr, t_map *map);
void	set_final(t_map *map);
void	setup_mlx(t_map *map);
void	validate(t_map *map);
#endif