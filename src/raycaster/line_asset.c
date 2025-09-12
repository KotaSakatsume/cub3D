/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_asset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 10:41:14 by mkuida            #+#    #+#             */
/*   Updated: 2025/09/12 17:56:56 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	set_distinct_and_wallside(t_game *game, t_linedraw *line)
{
	if ((line->hit_side) == 0)
	{
		(line->distinct) = ((line->tile_x) - (game->player_pos_x)) + ((1
					- (line->step_x)) / 2);
		(line->distinct) = (line->distinct) / (line->ray_x);
		if (line->ray_x > 0)
			(line->wall_side) = 'e';
		else
			(line->wall_side) = 'w';
	}
	else
	{
		(line->distinct) = ((line->tile_y) - (game->player_pos_y)) + ((1
					- (line->step_y)) / 2);
		(line->distinct) = (line->distinct) / (line->ray_y);
		if (line->ray_y > 0)
			(line->wall_side) = 's';
		else
			(line->wall_side) = 'n';
	}
}

static void	set_hitpoint(t_game *game, t_linedraw *line)
{
	if ((line->hit_side) == 0)
	{
		(line->hit_point) = (game->player_pos_y) + ((line->distinct)
				* (line->ray_y));
		if ((line->hit_point) < 0.0)
			(line->hit_point) = 0;
		else if ((line->hit_point) > 1)
			(line->hit_point) -= 1.0;
	}
	else
	{
		(line->hit_point) = (game->player_pos_x) + ((line->distinct)
				* (line->ray_x));
		if ((line->hit_point) < 0.0)
			(line->hit_point) = 0;
		else if ((line->hit_point) > 1)
			(line->hit_point) -= 1.0;
	}
	(line->hit_point) = (line->hit_point) - floor((line->hit_point));
}

static void	set_draw_wall_info(t_linedraw *line)
{
	(line->draw_wall_start) = (-(line->wall_height) / 2) + (WINDOW_HEIGHT / 2);
	if ((line->draw_wall_start) < 0)
		(line->draw_wall_start) = 0;
	(line->draw_wall_end) = ((line->wall_height) / 2) + (WINDOW_HEIGHT / 2);
	if ((line->draw_wall_end) >= WINDOW_HEIGHT)
		(line->draw_wall_end) = WINDOW_HEIGHT - 1;
}

static void	set_line_param(t_game *game, t_linedraw *line)
{
	set_distinct_and_wallside(game, line);
	set_hitpoint(game, line);
	if ((line->distinct) == 0)
		(line->wall_height) = WINDOW_HEIGHT;
	else
		(line->wall_height) = (WINDOW_HEIGHT / (line->distinct));
	if (line->wall_height < 1)
		line->wall_height = 1;
	set_draw_wall_info(line);
	(line->hit_x) = (line->tile_x);
	(line->hit_y) = (line->tile_y);
}

void	set_line_by_dda(t_game *game, t_linedraw *line)
{
	dda(line, game);
	set_line_param(game, line);
	return ;
}
