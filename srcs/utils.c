/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 11:13:20 by tparratt          #+#    #+#             */
/*   Updated: 2024/10/23 10:26:31 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_it_space(char *s, int i)
{
	if ((s[i] == 32 || (s[i] < 14 && s[i] > 8)))
		return (0);
	return (1);
}

/* checks whether or not a string is composed
entirely of whitespace characters */
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

/* prints error message to stderr and frees the map if needed */
void	print_error(char *str, t_map *map)
{
	ft_putendl_fd("Error", 2);
	if (str == NULL)
		perror("Map or texture file");
	else
		ft_putendl_fd(str, 2);
	if (map)
		free_map(map);
	exit(1);
}

/* the number of strings contained in a 2d array */
size_t	len_2d(char **arr)
{
	size_t	len;

	len = 0;
	while (arr[len])
		len++;
	len--;
	return (len);
}

/* strchr that works from the end of the string instead of the beginning */
char	*ft_strchr_rev(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str != '\0')
		str++;
	while (str >= s)
	{
		if (*str == (char)c)
			return (str);
		str--;
	}
	if (c == '\0')
		return (str);
	return (NULL);
}
