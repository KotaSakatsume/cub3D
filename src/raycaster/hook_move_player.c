/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 01:51:48 by mkuida            #+#    #+#             */
/*   Updated: 2025/08/28 01:51:48 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static bool	can_go_xy(t_game *game, double x, double y)
{
	int	int_x;
	int	int_y;

	if (x <= 0 || y <= 0)
		return (false);
	if (x >= (game->map_data.width) || y >= (game->map_data.height))
		return (false);
	int_x = (int)x;
	int_y = (int)y;
	printf("x = %f : int_x = %d : y = %f : int_y = %d\n", x, int_x, y, int_y);
	if (game->map_data.map[int_y][int_x] == '1')
	{
		printf("map[int_y][int_x] = %c\n", game->map_data.map[int_y][int_x]);
		return (false);
	}
	return (true);
}

int	move_w_player(t_game *game)
{
	double	move_speed;
	double	next_x;
	double	next_y;

	move_speed = 0.1 * MOVE_SPEED;
	next_x = (game->player_pos_x) + (game->player_dir_x) * move_speed;
	next_y = (game->player_pos_y) + (game->player_dir_y) * move_speed;
	if (can_go_xy(game, next_x, next_y) == true)
	{
		(game->player_pos_x) = next_x;
		(game->player_pos_y) = next_y;
		set_start_vision(game);
	}
	return (0);
}

int	move_a_player(t_game *game)
{
	double	move_speed;
	double	next_x;
	double	next_y;

	move_speed = 0.1 * MOVE_SPEED;
	next_x = (game->player_pos_x) + (game->player_dir_y) * move_speed;
	next_y = (game->player_pos_y) - (game->player_dir_x) * move_speed;
	if (can_go_xy(game, next_x, next_y) == true)
	{
		(game->player_pos_x) = next_x;
		(game->player_pos_y) = next_y;
		set_start_vision(game);
	}
	return (0);
}

int	move_s_player(t_game *game)
{
	double	move_speed;
	double	next_x;
	double	next_y;

	move_speed = 0.1 * MOVE_SPEED;
	next_x = (game->player_pos_x) - (game->player_dir_x) * move_speed;
	next_y = (game->player_pos_y) - (game->player_dir_y) * move_speed;
	if (can_go_xy(game, next_x, next_y) == true)
	{
		(game->player_pos_x) = next_x;
		(game->player_pos_y) = next_y;
		set_start_vision(game);
	}
	return (0);
}

int	move_d_player(t_game *game)
{
	double	move_speed;
	double	next_x;
	double	next_y;

	move_speed = 0.1 * MOVE_SPEED;
	next_x = (game->player_pos_x) - (game->player_dir_y) * move_speed;
	next_y = (game->player_pos_y) + (game->player_dir_x) * move_speed;
	if (can_go_xy(game, next_x, next_y) == true)
	{
		(game->player_pos_x) = next_x;
		(game->player_pos_y) = next_y;
		set_start_vision(game);
	}
	return (0);
}
