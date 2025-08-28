/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DDA.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:39:29 by mkuida            #+#    #+#             */
/*   Updated: 2025/08/28 14:58:59 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static bool	check_out_map(t_map *map, int X, int Y)
{
	if (X < -1 || Y < -1)
		return (true);
	if (X > (map->width) || Y > (map->height))
		return (true);
	return (false);
}

static bool	check_hit_wall(t_map *map, int X, int Y)
{
	if (map->map[Y][X] == '1')
		return (true);
	return (false);
}

void	DDA(t_linedraw *line, t_game *game)
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
		if (check_out_map(&(game->map_data), (line->tileX),
				(line->tileY)) == true)
		{
			printf("out map\n");
			printf("(line->tileX) = %d , (line->tileY) = %d\n", (line->tileX),
				(line->tileY));
			exit(1);
		}
		if (check_hit_wall(&(game->map_data), (line->tileX),
				(line->tileY)) == true)
			hit = 1;
	}
}
