/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:56:32 by kotasakatsu       #+#    #+#             */
/*   Updated: 2025/09/10 14:20:18 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_map(t_map *map)
{
	map->map = NULL;
	map->width = 0;
	map->height = 0;
	map->player_x = -1;
	map->player_y = -1;
	map->player_dir = 'N';
}

void	init_game(t_game *game)
{
	game->player_pos_x = 0.0;
	game->player_pos_y = 0.0;
	game->player_dir_x = 0.0;
	game->player_dir_y = 0.0;
	game->player_plane_x = 0.0;
	game->player_plane_y = 0.66;
	game->north_texture = NULL;
	game->south_texture = NULL;
	game->east_texture = NULL;
	game->west_texture = NULL;
	game->floor_color = -1;
	game->ceiling_color = -1;
	game->mlx = NULL;
	game->win = NULL;
	game->file_content = NULL;
	init_map(&game->map_data);
}
