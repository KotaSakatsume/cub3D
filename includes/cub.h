/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotasakatsume <kotasakatsume@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:07:57 by kotasakatsu       #+#    #+#             */
/*   Updated: 2025/08/16 14:53:25 by kotasakatsu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct s_game
{
    // マップ情報へのポインタ
    char        **map_data;
    int         map_width;
    int         map_height;

    // プレイヤー情報
    double      player_pos_x;
    double      player_pos_y;
    double      player_dir_x;
    double      player_dir_y;
    double      player_plane_x;
    double      player_plane_y;

    // テクスチャと色情報
    char        *north_texture;
    char        *south_texture;
    char        *east_texture;
    char        *west_texture;
    int         floor_color; // 例: RGB値をまとめた整数
    int         ceiling_color;

    // MiniLibX関連
    void        *mlx;
    void        *win;

}   t_game;


#endif