/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:13:20 by tparratt          #+#    #+#             */
/*   Updated: 2024/08/28 14:55:37 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_map(t_map *map)
{
	free(map->c);
    free(map->f);
    free(map->no);
    free(map->so);
    free(map->ea);
    free(map->we);
    free_2d(map->map);
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