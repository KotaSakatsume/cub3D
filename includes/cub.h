/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:07:57 by kotasakatsu       #+#    #+#             */
/*   Updated: 2025/08/27 11:51:15 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdbool.h>
# include <X11/X.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "libft.h"
# include "mlx.h"


#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define EXIT_FAILURE 1

//map関連の情報まとめ
typedef struct s_map
{
    char        **map; // 二次元配列でマップを保持
    int         width;    //x
    int         height;   //y
    int         player_x; //yoko
    int         player_y; //tate
    char        player_dir;//N S E W

}   t_map; 

typedef struct s_line_draw
{
	//初期条件
	double		rayX;
	double		rayY;
	double		deltaX;
	double		deltaY;

	double		cameraX;

	//結果
	int			draw_wall_start; //
	int			draw_wall_end; //
	int			wall_height; //

	char		wall_side;//

	int			hit_X;	//
	int			hit_Y;	//

	double		distinct; //
	
	double		hit_point; //0~1
}	t_line_draw;

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

//raycaster_set_test.c
int		set_test(t_game *game);

//raycaster_mlx_hook.c
void	set_mlx_hook(t_game *game);

//raycaster_set_textur.c
int		set_texture(t_game *game);

//raycaster_set_xml_imgs_wall_data.c
int		set_xml_imgs_wall_data(t_game *game);

//raycaster_set_line.c
void	init_line(t_line_draw *line, int X, t_game *game);
void	set_line_by_DDA(t_game *game, t_line_draw *line);
void	print_line(t_line_draw *line, int X);

//raycaster_my_mlx.c
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);

#endif