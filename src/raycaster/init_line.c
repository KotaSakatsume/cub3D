/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 12:14:50 by mkuida            #+#    #+#             */
/*   Updated: 2025/09/12 17:37:22 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static double set_delta(double ray)
{
	if (ray == 0)
		return (INFINITY);
	else
		return (fabs(1 / ray));
}

static void check_x(t_linedraw *line, t_game *game)
{
	if (line->ray_x < 0)
	{
		(line->step_x) = -1;
		(line->next_x_time) = ((game->player_pos_x) - (line->tile_x)) * (line->delta_x);
	}
	else
	{
		(line->step_x) = 1;
		(line->next_x_time) = (((line->tile_x) + 1) - (game->player_pos_x)) * (line->delta_x);
	}
}

static void check_y(t_linedraw *line, t_game *game)
{
	if (line->ray_y < 0)
	{
		(line->step_y) = -1;
		(line->next_y_time) = ((game->player_pos_y) - (line->tile_y)) * (line->delta_y);
	}
	else
	{
		(line->step_y) = 1;
		(line->next_y_time) = (((line->tile_y) + 1) - (game->player_pos_y)) * (line->delta_y);
	}
}

static void init_line_middle(t_linedraw *line, t_game *game)
{
	line->delta_x = set_delta(line->ray_x);
	line->delta_y = set_delta(line->ray_y);
	line->tile_x = (int)(game->player_pos_x);
	line->tile_y = (int)(game->player_pos_y);
	check_x(line, game);
	check_y(line, game);
}

void init_line(t_linedraw *line, int X, t_game *game)
{
	line->camera_x = ((2.0 * X) / (WINDOW_WIDTH - 1) - 1.0);
	line->ray_x = game->player_dir_x + ((game->player_plane_x) * (line->camera_x));
	line->ray_y = game->player_dir_y + ((game->player_plane_y) * (line->camera_x));
	init_line_middle(line, game);
	line->hit_side = -1;
	line->draw_wall_start = -1;
	line->draw_wall_end = -1;
	line->wall_height = -1;
	line->wall_side = ' ';
	line->hit_x = -1;
	line->hit_y = -1;
	line->distinct = -1;
	line->hit_point = -1;
}
