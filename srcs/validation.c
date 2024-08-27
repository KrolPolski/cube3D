#include "../includes/cub3d.h"

int  check_file_extension(char *arg)
{
    char    *ext;
    
    ext = ft_strchr(arg, '.');
    if (ext == NULL || ft_strncmp(ext, ".cub", 5))
    {
        ft_putendl_fd("Wrong file extension", 2);
        return (1);
    }
    return (0);
}