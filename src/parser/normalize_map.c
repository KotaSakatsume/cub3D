/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:07:57 by kotasakatsu       #+#    #+#             */
/*   Updated: 2025/09/09 17:00:01 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	get_max_width(char **map)
{
	int	i;
	int	max_len;
	int	len;

	i = 0;
	max_len = 0;
	while (map[i] != NULL)
	{
		len = strlen(map[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	return (max_len);
}

static void	pad_line(t_map *map, int index, int max_len)
{
	int		len;
	int		j;
	char	*new_line;

	len = strlen(map->map[index]);
	if (len < max_len)
	{
		new_line = malloc(sizeof(char) * (max_len + 1));
		if (!new_line)
			error_exit("Malloc failed in normalize_map", NULL);
		j = 0;
		while (j < len)
		{
			new_line[j] = map->map[index][j];
			j++;
		}
		while (j < max_len)
		{
			new_line[j] = ' ';
			j++;
		}
		new_line[j] = '\0';
		free(map->map[index]);
		map->map[index] = new_line;
	}
}

void	normalize_map(t_map *map)
{
	int	i;
	int	max_len;

	max_len = get_max_width(map->map);
	map->width = max_len;
	i = 0;
	while (map->map[i] != NULL)
	{
		pad_line(map, i, max_len);
		i++;
	}
	map->height = i;
}
