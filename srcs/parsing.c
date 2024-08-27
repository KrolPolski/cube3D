#include "../includes/cub3d.h"

static int identify_line(char *line)
{
    if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2) || !ft_strncmp(line, "EA", 2) || !ft_strncmp(line, "WE", 2) ||
            !ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
        return (0);
    else if (!ft_strncmp(line, "\n", 1)) // or all whitespace
        return (1);
    else
        return (2);
}

static int  *set_color_array(char *str)
{
    int     i;
    char    **str_arr;
    int     *int_arr;

    i = 0;
    str_arr = ft_split(str, ',');
    int_arr = (int *)malloc(3 * sizeof(int));
    while (str_arr[i])
    {
        int_arr[i] = ft_atoi(str_arr[i]);
        i++;
    }
    free_2d(str_arr);
    return (int_arr);
}

static int file_to_map(t_map *map, int i, char *line)
{
    char    **arr;
    char    *floor;
    char    *ceiling;

    if (identify_line(line) == 2)
    {
        map->map[i] = ft_strdup_mod(line);
        i++;
    }
    else if (identify_line(line) == 0)
    {
        arr = ft_split(line, ' ');
        if (!ft_strncmp(arr[0], "NO", 2))
            map->no = ft_strdup_mod(arr[1]);
        if (!ft_strncmp(arr[0], "SO", 2))
            map->so = ft_strdup_mod(arr[1]);
        if (!ft_strncmp(arr[0], "EA", 2))
            map->ea = ft_strdup_mod(arr[1]);
        if (!ft_strncmp(arr[0], "WE", 2))
            map->we = ft_strdup_mod(arr[1]);
        if (!ft_strncmp(arr[0], "F", 1))
        {
            floor = ft_strdup_mod(arr[1]);
            map->f = set_color_array(floor); 
            free(floor);
        }
        if (!ft_strncmp(arr[0], "C", 2))
        {
            ceiling = ft_strdup_mod(arr[1]);
            map->c = set_color_array(ceiling);
            free(ceiling);
        }
        free_2d(arr);
    }
    return (i);
}

void set_initial_map(char *arg, int lines, t_map *map)
{
    int     fd;
    char    *line;
    int     i;
    
    map->map = malloc((lines * sizeof(char *)) + 1);
    fd = open(arg, O_RDONLY);
    i = 0;
    line = get_next_line(fd);
    i = file_to_map(map, i, line);
    while (line)
    {
        free(line);
        line = get_next_line(fd);
        if (!line)
            break ;
        i = file_to_map(map, i, line);
    }
    map->map[i] = NULL;
    close(fd);
}

int  map_line_count(char *arg)
{
    int     fd;
    char    *line;
    int     no_of_lines;
    
    fd = open(arg, O_RDONLY);
    line = get_next_line(fd);
    no_of_lines = 0;
    if (identify_line(line) == 2)
        no_of_lines++;
    while (line)
    {
        free(line);
        line = get_next_line(fd);
        if (!line)
            break ;
        if (identify_line(line) == 2)
            no_of_lines++;
    }
    close(fd);
    return (no_of_lines);
}

static size_t   get_longest_len(t_map *map)
{
    int     i;
    size_t  len;

    i = 0;
    len = 0;
    while (map->map[i])
    {
        if (len < ft_strlen(map->map[i]))
            len = ft_strlen(map->map[i]);
        i++;
    }
    return (len);
}

static char *get_s2(size_t len, char *s1)
{
    size_t  i;
    char    *str;

    i = 0;
    str = malloc((len - ft_strlen(s1)) * sizeof(char) + 1);
    while (i < (len - ft_strlen(s1)))
    {
        str[i] = ' ';
        i++;
    }
    str[i] = '\0';
    return (str);
}

void set_final(t_map *map)
{
    int     i;
    size_t  len;
    char    *s1;
    char    *s2;
    char    *temp;

    len = get_longest_len(map);
    i = 0;
    while (map->map[i])
    {
        if (ft_strlen(map->map[i]) < len)
        {
            s1 = ft_strdup(map->map[i]);
            s2 = get_s2(len, s1);
            temp = ft_strjoin(s1, s2);
            free(map->map[i]);
            map->map[i] = ft_strdup(temp);
            free(temp);
            free(s1);
            free(s2);
        }
        i++;
    }
}