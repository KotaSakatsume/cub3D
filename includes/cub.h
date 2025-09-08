/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:07:57 by kotasakatsu       #+#    #+#             */
/*   Updated: 2025/09/08 18:58:40 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "libft.h"
// # include "mlx.h"
# include <stdbool.h>
// # include <X11/X.h
// # include <X11/Xlib.h>
// # include <X11/keysym.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define EXIT_FAILURE 1

// map関連の情報まとめ
typedef struct s_map
{
	char **map; // 二次元配列でマップを保持
	int				width;
	int				height;
	int player_x; // yoko
	int player_y; // tate
	char			player_dir;

}					t_map;

// mlb用の画像ファイル保管場所
typedef struct s_img
{
	void			*mlx_img;
	char			*addr;
	int				width;
	int				height;
	int				bpp;
	int				line_len;
	int				endian;
}					t_img;

typedef struct s_game
{
	// ★　↓いったんコメントアウトで変更前残しつつ変更
	// // マップ情報へのポインタ
	// char        **map_data;
	// int         map_width;
	// int         map_height;
	//　★　↑ここまで

	//　いったん以下に変更
	t_map			map_data;

	// プレイヤー情報
	double			player_pos_x;
	double			player_pos_y;
	double			player_dir_x;
	double			player_dir_y;
	double			player_plane_x;
	double			player_plane_y;

	// テクスチャと色情報
	char			*north_texture;
	char			*south_texture;
	char			*east_texture;
	char			*west_texture;
	int floor_color; // 例: RGB値をまとめた整数
	int				ceiling_color;

	// MiniLibX関連
	void			*mlx;
	void			*win;

	//以下新構造体、私の担当部分で作成します。
	t_img *north_img; // mkuida
	t_img *south_img; // mkuida
	t_img *east_img;  // mkuida
	t_img *west_img;  // mkuida

}					t_game;

typedef struct s_queue
{
	int				x;
	int				y;
	struct s_queue	*next;
}					t_queue;

// raycaster
int					set_test(t_game *game);
void				set_mlx_hook(t_game *game);
int					set_texture(t_game *game);

// parser

// parse.c
int					parse_file(t_game *game, char *filename);
void				parse_texture(t_game *game, const char *path,
						char **texture_path);
void				parse_color(t_game *game, const char *color_str,
						int *color);

// main.c
void				error_exit(char *message, t_game *game);

// inti_game
void				init_game(t_game *game);

char				*get_next_line(int fd);
// int			ft_putc(t_string *str, char c);
// char		ft_getc(int fd);
// int			extend_capacity(t_string *str);

// ft_split.c
char				**ft_split(char const *s, char c);

// val_map.c
void				validate_map(t_game *game);
void				find_player_loop(t_game *game, t_queue **queue);

// parse_co_and_tex.c
void				parse_color(t_game *game, const char *color_str,
						int *color);
void				parse_texture(t_game *game, const char *path,
						char **texture_path);

// read_file.c
char				**read_file(t_game *game, char *filename);

// set_player.c
void				set_player_start(t_game *game);

// normalize_map.c
void				normalize_map(t_map *map);

// find_player.c
void				find_player(t_game *game, t_queue **queue);
void				set_player_queue(t_queue **queue, int x, int y, int *found);
void				enqueue(t_queue **head, int x, int y);

// bfs.c
void				bfs_validate(t_game *game, int **visited, t_queue *queue);

// parse_utils.c
void				free_visited(int **visited, int height);
int					is_valid_char(char c);
int					is_player(char c);

#endif