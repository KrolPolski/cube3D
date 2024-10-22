/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:12:32 by tparratt          #+#    #+#             */
/*   Updated: 2024/10/22 12:41:43 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*returns the string of spaces to be added 
to any strings in the map that are shorter than the longest string in the map*/
static char	*get_s2(size_t len, char *s1, t_map *map)
{
	unsigned int	i;
	char			*str;

	i = 0;
	str = malloc((len - ft_strlen(s1)) * sizeof(char) + 1);
	if (!str)
		print_error("Memory allocation failure", map);
	while (i < (len - ft_strlen(s1)))
	{
		str[i] = ' ';
		i++;
	}
	str[i] = '\0';
	return (str);
}

static void	add_s2(int width, char *s1, t_map *map, int i)
{
	char	*s2;
	char	*temp;

	s2 = get_s2(width, s1, map);
	temp = ft_strjoin(s1, s2);
	if (!temp)
		print_error("Memory allocation failure", map);
	free(map->map[i]);
	map->map[i] = ft_strdup(temp);
	if (!map->map[i])
		print_error("Memory allocation failure", map);
	free(temp);
	free(s1);
	free(s2);
}

static size_t	map_width(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (str[i] == ' ')
		i--;
	i++;
	return (i);
}

static int	longest_str_i(t_map *map)
{
	int		i;
	int		longest_index;
	size_t	max_len;
	size_t	current_len;

	i = 0;
	max_len = 0;
	longest_index = -1;
	while (map->map[i])
	{
		current_len = ft_strlen(map->map[i]);
		if (current_len > max_len)
		{
			max_len = current_len;
			longest_index = i;
		}
		i++;
	}
	return (longest_index);
}

// sets the final map->map 2d array
void	set_final(t_map *map)
{
	int		i;
	size_t	width;
	int		idx;
	char	*s1;

	idx = longest_str_i(map);
	width = map_width(map->map[idx]);
	i = 0;
	while (map->map[i])
	{
		if (i == idx)
			s1 = ft_substr(map->map[idx], 0, width);
		else
			s1 = ft_strdup(map->map[i]);
		if (!s1)
			print_error("Memory allocation failure", map);
		add_s2(width, s1, map, i);
		i++;
	}
}
