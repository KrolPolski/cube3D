/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:11:02 by tparratt          #+#    #+#             */
/*   Updated: 2024/09/12 13:16:27 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	*set(char **str_arr, t_map *map, int *int_arr)
{
	int	i;
	int	j;

	i = 0;
	while (str_arr[i])
	{
		int_arr[i] = ft_atoi(str_arr[i]);
		j = 0;
		while (str_arr[i][j])
		{
			if (ft_isalpha(str_arr[i][j]) || (int_arr[i] < 0
					|| int_arr[i] > 255))
			{
				free_2d(str_arr);
				free(int_arr);
				print_error("RGB contains alphabets or integer not in correct range", map);
			}
			j++;
		}
		i++;
	}
	return (int_arr);
}

// creates int array by atoi-ing each string in ceiling and floor
static int	*set_color_array(char *str, t_map *map)
{
	char	**str_arr;
	int		*int_arr;
	int		len;

	str_arr = ft_split(str, ',');
	if (!str_arr)
		print_error("Memory allocation failure", map);
	len = len_2d(str_arr);
	if (len >= 3)
	{
		free_2d(str_arr);
		print_error("RGB contains too many integers", map);
	}
	int_arr = (int *)malloc(3 * sizeof(int));
	if (!int_arr)
		print_error("Memory allocation failure", map);
	int_arr = set(str_arr, map, int_arr);
	free_2d(str_arr);
	return (int_arr);
}

int	*set_color(char *str, char **arr, t_map *map)
{
	int	*res;

	str = ft_strdup_mod(arr[1]);
	if (!str)
		print_error("Memory allocation failure", map);
	res = set_color_array(str, map);
	if (!res)
		print_error("Memory allocation failure", map);
	free(str);
	return (res);
}