/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_rotate_player.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 02:01:50 by mkuida            #+#    #+#             */
/*   Updated: 2025/08/28 02:01:50 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	rotate_player_left(t_game *game)
{
	double oldDirX = game->player_dir_x;
	double oldPlaneX = game->player_plane_x;

	double ROTATE_SPEED = -1 * ROTATE_SPEED_DEGREE * 2 * M_PI / 360;
	
	game->player_dir_x = game->player_dir_x * cos(ROTATE_SPEED) - game->player_dir_y * sin(ROTATE_SPEED);
	game->player_dir_y = oldDirX * sin(ROTATE_SPEED) + game->player_dir_y * cos(ROTATE_SPEED);

	game->player_plane_x = game->player_plane_x * cos(ROTATE_SPEED) - game->player_plane_y * sin(ROTATE_SPEED);
	game->player_plane_y = oldPlaneX * sin(ROTATE_SPEED) + game->player_plane_y * cos(ROTATE_SPEED);
	set_start_vision(game);
	return (0);
}

int	rotate_player_right(t_game *game)
{
	double oldDirX = game->player_dir_x;
	double oldPlaneX = game->player_plane_x;

	double ROTATE_SPEED = 1 * ROTATE_SPEED_DEGREE * 2 * M_PI / 360;
	
	game->player_dir_x = game->player_dir_x * cos(ROTATE_SPEED) - game->player_dir_y * sin(ROTATE_SPEED);
	game->player_dir_y = oldDirX * sin(ROTATE_SPEED) + game->player_dir_y * cos(ROTATE_SPEED);

	game->player_plane_x = game->player_plane_x * cos(ROTATE_SPEED) - game->player_plane_y * sin(ROTATE_SPEED);
	game->player_plane_y = oldPlaneX * sin(ROTATE_SPEED) + game->player_plane_y * cos(ROTATE_SPEED);
	set_start_vision(game);
	return (0);
}