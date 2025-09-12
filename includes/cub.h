/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:07:57 by kotasakatsu       #+#    #+#             */
/*   Updated: 2025/09/12 18:06:52 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "libft.h"
# include "mlx.h"
# include <X11/X.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define FOV 90.0
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define WINDOW_MIN_WIDTH 100
# define WINDOW_MIN_HEIGHT 100
# define ROTATE_SPEED_DEGREE 1
# define MOVE_SPEED 1
# define EXIT_FAILURE 1

// struct

// for_map
//(width=x,height=y)
typedef struct s_map
{
	char			**map;
	int				width;
	int				height;
	int				player_x;
	int				player_y;
	char			player_dir;
}					t_map;

// for_raycast
//(hit_point = 0~1)
typedef struct s_linedraw
{
	double			camera_x;
	double			ray_x;
	double			ray_y;
	double			delta_x;
	double			delta_y;
	int				step_x;
	int				step_y;
	int				tile_x;
	int				tile_y;
	double			next_x_time;
	double			next_y_time;
	int				hit_side;
	int				draw_wall_start;
	int				draw_wall_end;
	int				wall_height;
	char			wall_side;
	int				hit_x;
	int				hit_y;
	double			distinct;
	double			hit_point;
}					t_linedraw;

// for minilib
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

// for all
// fllor_color contain RGB
typedef struct s_game
{
	t_map			map_data;
	double			player_pos_x;
	double			player_pos_y;
	double			player_dir_x;
	double			player_dir_y;
	double			player_plane_x;
	double			player_plane_y;
	char			*north_texture;
	char			*south_texture;
	char			*east_texture;
	char			*west_texture;
	int				floor_color;
	int				ceiling_color;
	void			*mlx;
	void			*win;
	t_img			north_img;
	t_img			south_img;
	t_img			east_img;
	t_img			west_img;
	t_img			screen;
	char			**file_content;
}					t_game;

typedef struct s_queue
{
	int				x;
	int				y;
	struct s_queue	*next;
}					t_queue;

// main.c
void				error_exit(char *message, t_game *game);
void				free_file_content(char **file_content);

// parser

// parser_parse.c
int					parse_file(t_game *game, char *filename);
void				parse_texture(t_game *game, const char *path,
						char **texture_path);
void				parse_color(t_game *game, const char *color_str,
						int *color);
int					is_empty_line(char *line);
const char			*skip_spaces(const char *s);
int					is_map_line(char *line);
void				add_map_line(t_map *map, const char *line);
int					check_extension(const char *filename,
						const char *extension);

// parser_inti_game
void				init_game(t_game *game);

char				*get_next_line(int fd);

// parser_ft_split.c
char				**ft_split(char const *s, char c);

// parser_val_map.c
void				validate_map(t_game *game);
void				find_player_loop(t_game *game, t_queue **queue);

// parser_parse_co_and_tex.c
void				parse_color(t_game *game, const char *color_str,
						int *color);
void				parse_texture(t_game *game, const char *path,
						char **texture_path);

// parser_read_file.c
char				**read_file(t_game *game, char *filename);

// parser_set_player.c
void				set_player_start(t_game *game);

// parser_normalize_map.c
void				normalize_map(t_map *map);

// parser_find_player.c
void				find_player(t_game *game, t_queue **queue);
void				set_player_queue(t_queue **queue, int x, int y, int *found);
void				enqueue(t_queue **head, int x, int y);

// parser_bfs.c
void				bfs_validate(t_game *game, int **visited, t_queue *queue);

// parser_parse_utils.c
void				free_visited(int **visited, int height);
int					is_valid_char(char c);
int					is_player(char c);

// raycaster

// raycaster_DDA.c
void				dda(t_linedraw *line, t_game *game);

// raycaster_hook_move_player.c
int					move_w_player(t_game *game);
int					move_a_player(t_game *game);
int					move_s_player(t_game *game);
int					move_d_player(t_game *game);

// raycaster_hook_ritate_player.c
int					rotate_player_left(t_game *game);
int					rotate_player_right(t_game *game);

// raycaster_init_line.c
void				init_line(t_linedraw *line, int X, t_game *game);
void				free_game(t_game *game);

// raycaster_line_asset.c
void				set_line_by_dda(t_game *game, t_linedraw *line);

// raycaster_my_mlx.c
void				my_mlx_pixel_put(t_img *data, int x, int y, int color);
int					my_mlx_pixel_get(t_img *data, int x, int y);

// raycaster_ray_util.c
int					max(int x, int y);
int					min(int x, int y);
void				free_game(t_game *game);
void				destroy_all_image(t_game *game);
void				print_line(t_linedraw *line, int X);

// raycaster_set_mlx_hook.c
void				set_mlx_hook(t_game *game);

// raycaster_set_test.c
int					set_test(t_game *game);

// raycaster_set_textur.c
int					set_texture(t_game *game);

// raycaster_set_start_vision.c
void				set_start_vision(t_game *game);

// raycaster_set_xml_imgs_wall_data.c
int					set_mlx_imgs_wall_data(t_game *game);

#endif