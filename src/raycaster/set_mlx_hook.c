/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_mlx_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:15:29 by mkuida            #+#    #+#             */
/*   Updated: 2025/08/18 17:11:16 by mkuida           ###   ########.fr       */
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
	// if (keysym == (int) 's' && data->state == PLAYING)
	// 	move_player(data, 1, 0);
	// else if (keysym == (int) 'a' && data->state == PLAYING)
	// 	move_player(data, 0, -1);
	// else if (keysym == (int) 'w' && data->state == PLAYING)
	// 	move_player(data, -1, 0);
	// else if (keysym == (int) 'd' && data->state == PLAYING)
	// 	move_player(data, 0, 1);
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
