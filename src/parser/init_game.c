/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:56:32 by kotasakatsu       #+#    #+#             */
/*   Updated: 2025/08/22 12:07:08 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_map(t_map *map)
{
	// マップの初期化
	map->map = NULL; // マップデータは後で読み込む
	map->width = 0;
	map->height = 0;
	map->player_x = -1;    // 初期値は無効な位置
	map->player_y = -1;    // 初期値は無効な位置
	map->player_dir = 'N'; // 初期方向は北
}

void	init_game(t_game *game)
{
	// ゲームの初期化
	game->player_pos_x = 0.0;
	game->player_pos_y = 0.0;
	game->player_dir_x = 0.0;
	game->player_dir_y = 0.0;
	game->player_plane_x = 0.0;
	game->player_plane_y = 0.66; // 90度の視野を持つための初期値
	game->north_texture = NULL;
	game->south_texture = NULL;
	game->east_texture = NULL;
	game->west_texture = NULL;
	game->floor_color = 0x000000;   // 黒色
	game->ceiling_color = 0xFFFFFF; // 白色
	game->mlx = NULL;
	game->win = NULL;
	init_map(&game->map_data);
}
