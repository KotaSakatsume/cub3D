/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:39:29 by mkuida            #+#    #+#             */
/*   Updated: 2025/09/11 16:20:00 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static bool	check_out_map(t_map *map, t_linedraw *line)
{
	int	x;
	int	y;

	x = (line->tileX);
	y = (line->tileY);
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
	printf("error : out  map\n");
	printf("(line->tileX) = %d , (line->tileY) = %d\n", (line->tileX),
		(line->tileY));
	exit(1);
}

void	dda(t_linedraw *line, t_game *game)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if ((line->nextXtime) < (line->nextYtime))
		{
			(line->nextXtime) += (line->deltaX);
			(line->tileX) += (line->stepX);
			(line->hit_side) = 0;
		}
		else
		{
			(line->nextYtime) += (line->deltaY);
			(line->tileY) += (line->stepY);
			(line->hit_side) = 1;
		}
		if (check_out_map(&(game->map_data), line) == true)
			out_map(game, line);
		if (check_hit_wall(&(game->map_data), (line->tileX),
				(line->tileY)) == true)
			hit = 1;
	}
}
