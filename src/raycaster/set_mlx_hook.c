/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mlx_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:15:29 by mkuida            #+#    #+#             */
/*   Updated: 2025/08/28 01:23:17 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	handle_close(t_game *game)
{
	(void)game;
	// destroy_image_before_close(data);
	// mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	// mlx_destroy_display(data->mlx_ptr);
	// data->win_ptr = NULL;
	// free(data->mlx_ptr);
	// free_map(data->map);
	// free(data);
	// exit(0);
	exit (0);
}

static int	expose_hook(t_game *game)
{
	static bool	first_accsess = true;

	if (first_accsess == true)
	{
		first_accsess = false;
		return (0);
	}
	handle_close(game);
	return (0);
}

static int	rotate_player_left(t_game *game)
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

static int	rotate_player_right(t_game *game)
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

static int move_w_player(t_game *game)
{
	double move_speed = 0.1 * MOVE_SPEED;

	(game->player_pos_x) = (game->player_pos_x) + (game->player_dir_x) * move_speed;
	(game->player_pos_y) = (game->player_pos_y) + (game->player_dir_y) * move_speed;
	set_start_vision(game);
	return (0);
}

static int move_a_player(t_game *game)
{
	double move_speed = 0.1 * MOVE_SPEED;

	(game->player_pos_x) = (game->player_pos_x) + (game->player_dir_y) * move_speed;
	(game->player_pos_y) = (game->player_pos_y) - (game->player_dir_x) * move_speed;
	set_start_vision(game);
	return (0);
}

static int move_s_player(t_game *game)
{
	double move_speed = 0.1 * MOVE_SPEED;

	(game->player_pos_x) = (game->player_pos_x) - (game->player_dir_x) * move_speed;
	(game->player_pos_y) = (game->player_pos_y) - (game->player_dir_y) * move_speed;
	set_start_vision(game);
	return (0);
}

static int move_d_player(t_game *game)
{
	double move_speed = 0.1 * MOVE_SPEED;

	(game->player_pos_x) = (game->player_pos_x) - (game->player_dir_y) * move_speed;
	(game->player_pos_y) = (game->player_pos_y) + (game->player_dir_x) * move_speed;
	set_start_vision(game);
	return (0);
}

static int	key_handle(int keysym, t_game *game)
{
	if (keysym == (int) 'w')
		move_w_player(game);
	else if (keysym == (int) 'a')
		move_a_player(game);
	else if (keysym == (int) 's')
		move_s_player(game);
	else if (keysym == (int) 'd')
		move_d_player(game);
	else if (keysym == XK_Left)
		rotate_player_left(game);
	else if (keysym == XK_Right)
		rotate_player_right(game);
	if (keysym == XK_Escape)
		handle_close(game);
	return (0);
}


void	set_mlx_hook(t_game *game)
{
	mlx_hook(game->win, Expose, ExposureMask, &expose_hook, game);
	mlx_hook(game->win, DestroyNotify, StructureNotifyMask, &handle_close,game);
	mlx_hook(game->win, KeyPress, KeyPressMask, &key_handle, game);
}
