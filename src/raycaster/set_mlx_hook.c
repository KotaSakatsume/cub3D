/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mlx_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:15:29 by mkuida            #+#    #+#             */
/*   Updated: 2025/08/28 02:03:20 by mkuida           ###   ########.fr       */
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
	else if (keysym == XK_Escape)
		handle_close(game);
	return (0);
}


void	set_mlx_hook(t_game *game)
{
	mlx_hook(game->win, Expose, ExposureMask, &expose_hook, game);
	mlx_hook(game->win, DestroyNotify, StructureNotifyMask, &handle_close,game);
	mlx_hook(game->win, KeyPress, KeyPressMask, &key_handle, game);
}
