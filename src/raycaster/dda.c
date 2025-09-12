/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:39:29 by mkuida            #+#    #+#             */
/*   Updated: 2025/09/12 17:56:38 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static bool	check_out_map(t_map *map, t_linedraw *line)
{
	int	x;
	int	y;

	x = (line->tile_x);
	y = (line->tile_y);
	if (x < 0 || y < 0)
		return (true);
	if (x >= (map->width) || y >= (map->height))
		return (true);
	return (false);
}

static bool	check_hit_wall(t_map *map, int X, int Y)
{
	if (map->map[Y][X] == '1')
		return (true);
	return (false);
}

static void	out_map(t_game *game, t_linedraw *line)
{
	(void)*game;
	ft_printf("error : out  map\n");
	ft_printf("(line->tile_x) = %d , (line->tile_y) = %d\n", (line->tile_x),
		(line->tile_y));
	exit(1);
}

void	dda(t_linedraw *line, t_game *game)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if ((line->next_x_time) < (line->next_y_time))
		{
			(line->next_x_time) += (line->delta_x);
			(line->tile_x) += (line->step_x);
			(line->hit_side) = 0;
		}
		else
		{
			(line->next_y_time) += (line->delta_y);
			(line->tile_y) += (line->step_y);
			(line->hit_side) = 1;
		}
		if (check_out_map(&(game->map_data), line) == true)
			out_map(game, line);
		if (check_hit_wall(&(game->map_data), (line->tile_x),
				(line->tile_y)) == true)
			hit = 1;
	}
}
