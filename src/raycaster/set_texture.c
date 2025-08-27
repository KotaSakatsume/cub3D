/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 00:08:36 by mkuida            #+#    #+#             */
/*   Updated: 2025/08/27 11:56:45 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	start_mlx(t_game *game)
{
	//上限？
	if(WINDOW_WIDTH < 1 || WINDOW_HEIGHT < 1)
	{
		perror("mlx_init : check your WINDOW_SIZE");
		//exitなので修正必要
		exit(EXIT_FAILURE);
	}

	//init_mlx
	game->mlx = mlx_init();
	if(game->mlx == NULL)
	{
		perror("mlx_init");
		//exitなので修正必要
		exit(EXIT_FAILURE);
	}

	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,"cub3D");
	if (game->win == NULL)
	{
		perror("mlx_new_window");
		exit(EXIT_FAILURE);
	}
	return (0);
}

void set_pp(t_game *game)
{
	double FOV = 90.0;
	double player_plane_length = tan( M_PI * (FOV/2) / 180 );

	//直行
	//１を右、ー１を左にセットする
	game->player_plane_x = -(game->player_dir_y) * player_plane_length;
	game->player_plane_y = (game->player_dir_x) * player_plane_length;
}


static void set_start_player_posi(t_game *game)
{
	//xy set
	game->player_pos_x = (game->map_data.player_x) + 0.5;
	game->player_pos_y = (game->map_data.player_y) + 0.5;


	// posi set
	if(game->map_data.player_dir == 'N')
		game->player_dir_y = -1;
	else if(game->map_data.player_dir == 'E')
		game->player_dir_x = 1;
	else if(game->map_data.player_dir == 'W')
		game->player_dir_x = -1;
	else if(game->map_data.player_dir == 'S')
		game->player_dir_y = 1;
	else
	{
		printf("error : set_player\n");
		exit(1);
	}
	set_pp(game);
}

void set_start_vision(t_game *game)
{
	int X = 0;
	t_line_draw line;
	t_img img;
	img.mlx_img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.mlx_img, &img.bpp, &img.line_len, &img.endian);

	// printf("①\n");

	while(X < WINDOW_WIDTH)
	{
		// printf("A\n");
		init_line(&line, X, game);
		// printf("B\n");
		set_line_by_DDA(game,&line);
		// printf("C\n");
		// set_pixcel(game);
		// test
		// ceiling (fixed test color)
		for (int y = 0; y < line.draw_wall_start; y++)
		{
			my_mlx_pixel_put(&img, X, y,game->ceiling_color);
		}
		// wall
		for (int y = (line.draw_wall_start); y <= (line.draw_wall_end); y++)
		{
			my_mlx_pixel_put(&img, X, y, 0xFF0000);
		}
		// floor (fixed test color)
		for (int y = (line.draw_wall_end + 1); y < WINDOW_HEIGHT; y++)
		{
			my_mlx_pixel_put(&img, X, y, game->floor_color);
		}
		print_line(&line,X);
		X++;
	}
	mlx_put_image_to_window(game->mlx, game->win, img.mlx_img, 0, 0);
}

int set_texture(t_game *game)
{
	start_mlx(game);
	printf("end : set_texture : start_mlx\n");

	set_xml_imgs_wall_data(game);
	printf("end : set_texture : set_imgs_data\n");

	set_start_player_posi(game);
	printf("end : set_texture : set_player\n");

	set_start_vision(game);
	printf("end : set_texture : set_start_vision\n");

	return (0);
}
