/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_rotate_player.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 02:01:50 by mkuida            #+#    #+#             */
/*   Updated: 2025/08/28 16:28:10 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	rotate_player_left(t_game *game)
{
	double	old_dirx;
	double	old_planex;
	double	rotate_speed;

	old_dirx = game->player_dir_x;
	old_planex = game->player_plane_x;
	rotate_speed = -1 * ROTATE_SPEED_DEGREE * 2 * M_PI / 360;
	game->player_dir_x = game->player_dir_x * cos(rotate_speed)
		- game->player_dir_y * sin(rotate_speed);
	game->player_dir_y = old_dirx * sin(rotate_speed) + game->player_dir_y
		* cos(rotate_speed);
	game->player_plane_x = game->player_plane_x * cos(rotate_speed)
		- game->player_plane_y * sin(rotate_speed);
	game->player_plane_y = old_planex * sin(rotate_speed) + game->player_plane_y
		* cos(rotate_speed);
	set_start_vision(game);
	return (0);
}

int	rotate_player_right(t_game *game)
{
	double	old_dirx;
	double	old_planex;
	double	rotate_speed;

	old_dirx = game->player_dir_x;
	old_planex = game->player_plane_x;
	rotate_speed = 1 * ROTATE_SPEED_DEGREE * 2 * M_PI / 360;
	game->player_dir_x = game->player_dir_x * cos(rotate_speed)
		- game->player_dir_y * sin(rotate_speed);
	game->player_dir_y = old_dirx * sin(rotate_speed) + game->player_dir_y
		* cos(rotate_speed);
	game->player_plane_x = game->player_plane_x * cos(rotate_speed)
		- game->player_plane_y * sin(rotate_speed);
	game->player_plane_y = old_planex * sin(rotate_speed) + game->player_plane_y
		* cos(rotate_speed);
	set_start_vision(game);
	return (0);
}
