/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:13:20 by tparratt          #+#    #+#             */
/*   Updated: 2024/08/29 11:48:48 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_map(t_map *map)
{
	if (map->c)
	{
		ft_printf("ONEEEE\n");
		free(map->c);
	}
	if (map->f)
	{
		ft_printf("TWOOOO\n");
    	free(map->f);
	}
	if (map->ceiling)
	{
		ft_printf("ONE\n");
		free(map->c);
	}
	if (map->floor)
	{
		ft_printf("TWO\n");
    	free(map->f);
	}
	if (map->no)
	{
		ft_printf("THREE\n");
    	free(map->no);
	}
	if (map->so)
	{
		ft_printf("FOUR\n");
    	free(map->so);
	}
	if (map->ea)
	{
		ft_printf("FIVE\n");
    	free(map->ea);
	}
	if (map->we)
	{
		ft_printf("SIX\n");
    	free(map->we);
	}
	if (map->map[0])
	{
		ft_printf("SEVEN\n");
    	free_2d(map->map);
	}
}

char	*ft_strdup_mod(const char *s1)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*res;

	len = ft_strlen(s1);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		if (s1[i] != '\n')
		{
			res[j] = s1[i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	return (res);
}

void free_2d(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
		if (arr[i])
        	free(arr[i]);
        i++;
    }
    free(arr);
}

void print_2d(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
    {
        ft_putendl_fd(arr[i], 1);
        i++;
    }
}

static int	is_it_space(char *s, int i)
{
	if ((s[i] == 32 || (s[i] < 14 && s[i] > 8)))
		return (0);
	return (1);
}

int	all_whitespace(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!is_it_space(line, i))
			i++;
		else
			return (0);
	}
	return (1);
}

void	print_error(char *str)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(str, 2);
	exit(1);
}

size_t	len_2d(char **arr)
{
	size_t len;

    len = 0;
    while (arr[len])
        len++;
    len--;
	return (len);
}