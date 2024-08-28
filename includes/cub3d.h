#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h>
#include <fcntl.h>
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

typedef struct s_info
{
	int s_width;
	int s_height;
	mlx_t *mlx;
	t_map *map;

} t_info;

int 	check_file_extension(char *arg);
char	*ft_strdup_mod(const char *s1);
void	free_2d(char **arr);
void	print_2d(char **arr);
int  	map_line_count(char *arg);
void 	set_initial_map(char *arg, int lines, t_map *map);
void 	set_final(t_map *map);
void	setup_mlx(t_map *map);

#endif