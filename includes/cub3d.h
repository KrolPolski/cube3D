#ifndef CUB3D_H
# define CUB3D_H
# define BPP sizeof(int32_t)
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include "../libft/include/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_map
{
	char    **map;
 	char    *no;
    char    *so;
    char    *ea;
    char    *we;
	int		*f;
	int		*c;
}				t_map;

typedef struct s_images
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*ea;
	mlx_texture_t	*we;
	mlx_image_t		*fg;
	mlx_image_t		*bg;
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

} t_info;

int		get_rgba(int r, int g, int b, int a);
int 	check_file_extension(char *arg);
char	*ft_strdup_mod(const char *s1);
void	free_2d(char **arr);
void	print_2d(char **arr);
int  	map_line_count(char *arg);
void 	set_initial_map(char *arg, int lines, t_map *map);
void 	set_final(t_map *map);
void	setup_mlx(t_map *map);

#endif