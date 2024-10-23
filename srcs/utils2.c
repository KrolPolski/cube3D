/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:25:46 by tparratt          #+#    #+#             */
/*   Updated: 2024/10/23 10:04:26 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* creates a copy of map->map for use in fill */
void	copy_map(t_map *map)
{
	int	len;
	int	i;

	len = 0;
	len = len_2d(map->map);
	map->copy = malloc((len + 2) * sizeof(char *));
	if (!map->copy)
		print_error("Memory allocation failure", map);
	i = 0;
	while (i <= len)
	{
		map->copy[i] = ft_strdup(map->map[i]);
		if (!map->copy[i])
			print_error("Memory allocation failure", map);
		i++;
	}
	map->copy[i] = NULL;
}

void	free_map(t_map *map)
{
	if (map->c)
		free(map->c);
	if (map->f)
		free(map->f);
	if (map->ceiling)
		free(map->ceiling);
	if (map->floor)
		free(map->floor);
	if (map->no)
		free(map->no);
	if (map->so)
		free(map->so);
	if (map->ea)
		free(map->ea);
	if (map->we)
		free(map->we);
	if (map->map[0])
		free_2d(map->map);
}

/* modified ft_strdup to not include newline character in duplication */
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

void	free_2d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (arr[i])
			free(arr[i]);
		i++;
	}
	free(arr);
}

void	print_2d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		ft_putendl_fd(arr[i], 1);
		i++;
	}
}
