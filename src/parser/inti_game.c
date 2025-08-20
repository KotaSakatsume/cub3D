/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inti_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotasakatsume <kotasakatsume@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:56:32 by kotasakatsu       #+#    #+#             */
/*   Updated: 2025/08/20 18:22:22 by kotasakatsu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void inti_game(t_game *game)
{
    // ゲームの初期化
    game -> player_pos_x = 0.0;
    game -> player_pos_y = 0.0;
    game -> player_dir_x = 0.0;
    game -> player_dir_y = 0.0;
    game -> player_plane_x = 0.0;
    game -> player_plane_y = 0.66; // 90度の視野を持つための初期値
    game -> north_texture = NULL;
    game -> south_texture = NULL;
    game -> east_texture = NULL;
    game -> west_texture = NULL;
    game -> floor_color = 0x000000; // 黒色
    game -> ceiling_color = 0xFFFFFF; // 白色
    game -> mlx = NULL;
    game -> win = NULL;
    
}
