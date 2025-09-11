/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:07:57 by kotasakatsu       #+#    #+#             */
/*   Updated: 2025/09/09 12:24:12 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	set_player_position(t_game *game, int x, int y, char c)
{
	game->map_data.player_x = x;
	game->map_data.player_y = y;
	game->map_data.player_dir = c;
	game->map_data.map[y][x] = '0';
}

static void	check_and_set_player(t_game *game, int x, int y, int *found)
{
	char	c;

	c = game->map_data.map[y][x];
	if (is_player_char(c))
	{
		if (*found)
			error_exit("Multiple player positions found", game);
		set_player_position(game, x, y, c);
		*found = 1;
	}
}

void	set_player_start(t_game *game)
{
	int	y;
	int	x;
	int	found;

	found = 0;
	y = 0;
	while (y < game->map_data.height)
	{
		x = 0;
		while (x < game->map_data.width)
		{
			check_and_set_player(game, x, y, &found);
			x++;
		}
		y++;
	}
	if (!found)
		error_exit("No player position found", game);
}
