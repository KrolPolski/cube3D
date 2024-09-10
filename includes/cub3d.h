#ifndef CUB3D_H
# define CUB3D_H
# define BPP sizeof(int32_t)
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>
#include "../libft/include/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_map
{
	char    **map;
	int		start_i;
	int		start_j;
	char	**copy;
 	char    *no;
    char    *so;
    char    *ea;
    char    *we;
	char	*floor;
	char	*ceiling;
	int		*f;
	int		*c;
	int 	x_len;
	int 	y_len;
	int 	sq_w;
	int		sq_h;
	int 	sq;
}				t_map;


typedef struct s_images
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*ea;
	mlx_texture_t	*we;
	mlx_image_t		*fg;
	mlx_image_t		*world;
	mlx_image_t		*bg;
	mlx_image_t		*plyr;
	mlx_image_t		*map;
} t_images;

enum e_dir
{
	north,
	east,
	south,
	west,
	error,
};

typedef struct s_info
{
	int s_width;
	int s_height;
	mlx_t *mlx;
	t_map *map;
	t_images *img;
	double	p_x;
	double	p_y;
	double	p_orient;
	double  ray_x;
	double	ray_y;
	double	ray_orient;
	double	rend_dist;
	bool	map_visible;
	double	map_size_factor;
	int		map_width;
	int		map_height;

} t_info;

char	detect_square(t_map *map, double x, double y);
void	raycaster(mlx_t *mlx, t_map *map, t_images *img, t_info *info);
void	draw_2d_player(mlx_t *mlx, t_map *map, t_info *info);
void	ft_single_press_hook(mlx_key_data_t keydata, void *param);
int		get_rgba(int r, int g, int b, int a);
int		invalid_file_extension(char *arg, char *ext);
char	*ft_strchr_rev(const char *s, int c);
char	*ft_strdup_mod(const char *s1);
void	free_2d(char **arr);
void	print_2d(char **arr);
int  	map_line_count(char *arg);
void 	set_initial_map(char *arg, t_map *map);
void 	set_final(t_map *map);
void    parse(char **argv, t_map *map);
void    validate(t_map *map);
int		all_whitespace(char *line);
void	free_map(t_map *map);
void	print_error(char *str, t_map *map);
size_t	len_2d(char **arr);
void	check_walls(t_map *map);
void	setup_mlx(t_map *map);

#endif