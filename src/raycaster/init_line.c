/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:14:50 by mkuida            #+#    #+#             */
/*   Updated: 2025/08/28 16:46:04 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static double	set_delta(double ray)
{
	if (ray == 0)
		return (INFINITY);
	else
		return (fabs(1 / ray));
}

static void	check_x(t_linedraw *line, t_game *game)
{
	if (line->rayX < 0)
	{
		(line->stepX) = -1;
		(line->nextXtime) = ((game->player_pos_x) - (line->tileX))
			* (line->deltaX);
	}
	else
	{
		(line->stepX) = 1;
		(line->nextXtime) = (((line->tileX) + 1) - (game->player_pos_x))
			* (line->deltaX);
	}
}

static void	check_y(t_linedraw *line, t_game *game)
{
	if (line->rayY < 0)
	{
		(line->stepY) = -1;
		(line->nextYtime) = ((game->player_pos_y) - (line->tileY))
			* (line->deltaY);
	}
	else
	{
		(line->stepY) = 1;
		(line->nextYtime) = (((line->tileY) + 1) - (game->player_pos_y))
			* (line->deltaY);
	}
}

static void	init_line_middle(t_linedraw *line, t_game *game)
{
	line->deltaX = set_delta(line->rayX);
	line->deltaY = set_delta(line->rayY);
	line->tileX = (int)(game->player_pos_x);
	line->tileY = (int)(game->player_pos_y);
	check_x(line, game);
	check_y(line, game);
}

void	init_line(t_linedraw *line, int X, t_game *game)
{
	line->cameraX = ((2.0 * X) / (WINDOW_WIDTH - 1) - 1.0);
	line->rayX = game->player_dir_x + ((game->player_plane_x)
			* (line->cameraX));
	line->rayY = game->player_dir_y + ((game->player_plane_y)
			* (line->cameraX));
	init_line_middle(line, game);
	line->hit_side = -1;
	line->draw_wall_start = -1;
	line->draw_wall_end = -1;
	line->wall_height = -1;
	line->wall_side = ' ';
	line->hit_X = -1;
	line->hit_Y = -1;
	line->distinct = -1;
	line->hit_point = -1;
}
