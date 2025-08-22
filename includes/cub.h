/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotasakatsume <kotasakatsume@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:07:57 by kotasakatsu       #+#    #+#             */
/*   Updated: 2025/08/20 19:35:47 by kotasakatsu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "libft.h"
// # include "mlx.h"
# include <stdbool.h>
// # include <X11/X.h>
// # include <X11/Xlib.h>
// # include <X11/keysym.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define EXIT_FAILURE 1

//map関連の情報まとめ
typedef struct s_map
{
    char        **map; // 二次元配列でマップを保持
    int         width;
    int         height;
    int         player_x; //yoko
    int         player_y; //tate
    char        player_dir;

}   t_map; 

//mlb用の画像ファイル保管場所
typedef struct s_img
{
    void            *mlx_img;
    char            *addr;
    int                width;
    int                height;
    int                bpp;
    int                line_len;
    int                endian;
}                    t_img;

typedef struct s_game
{

	// ★　↓いったんコメントアウトで変更前残しつつ変更
    // // マップ情報へのポインタ
    // char        **map_data;
    // int         map_width;
    // int         map_height;
	//　★　↑ここまで

	//　いったん以下に変更
	t_map		map_data;

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

    //以下新構造体、私の担当部分で作成します。
    t_img        *north_img;    //mkuida
    t_img        *south_img;    //mkuida
    t_img        *east_img;    //mkuida
    t_img        *west_img;    //mkuida
	
}   t_game;


//raycaster
int		set_test(t_game *game);
void	set_mlx_hook(t_game *game);
int		set_texture(t_game *game);

//parser

//inti_game
void init_game(t_game *game);

#endif