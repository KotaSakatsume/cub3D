/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 00:08:36 by mkuida            #+#    #+#             */
/*   Updated: 2025/08/28 13:33:51 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	start_mlx(t_game *game)
{
	//上限と下弦の値はこれでいい？
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

static void set_pp(t_game *game)
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

static void print_wall_color(t_game *game, t_line_draw *line, t_img *img,int X)
{
	t_img *original_data;
	int test = original_data->width;
	int original_x;
	original_x = (line->hit_point)*(original_data->width);

	
	if(line -> wall_side == 'w')
	{
		original_data = &game->west_img;
		original_x = (1.0 - (line->hit_point)) * (original_data->width);
	}
	else if(line -> wall_side == 'n')
	{
		original_data = &game->north_img;
		original_x = (line->hit_point) * (original_data->width);
	}
	else if(line -> wall_side == 'e')
	{
		original_data = &game->east_img;
		original_x = (line->hit_point) * (original_data->width);
	}
	else if(line -> wall_side == 's')
	{
		original_data = &game->south_img;
		original_x = (1.0 - (line->hit_point)) * (original_data->width);
	}
	else
	{
		printf("originaldata error\n");
		exit(1);
	}
	
	// int test = original_data->width;
	// int original_x = (line->hit_point)*(original_data->width);
	// printf("hit_point = %f : original_width = %d : original_x = %d\n",line->hit_point, original_data->width , original_x);
	int wall_color;

	for (int y = (line->draw_wall_start); y <= (line->draw_wall_end); y++)
	{
		double y_raito;
		y_raito = ((double)(y - (line->draw_wall_start))/(line->wall_height));
		// printf("y_raito = %f\n",y_raito);
		int original_y = (original_data->height)*(y_raito);
		// printf("original_x = %d : original_y = %d\n",original_x,original_y);
		wall_color = my_mlx_pixel_get(original_data, original_x, original_y);
		my_mlx_pixel_put(img, X, y, wall_color);
	}
}

void print_tex(t_game *game, t_line_draw *line, t_img *img, int X)
{
	//ceil
	for (int y = 0; y < line->draw_wall_start; y++)
		my_mlx_pixel_put(img, X, y, game->ceiling_color);

	// wall
	print_wall_color(game,line,img,X);

	
	// for (int y = (line->draw_wall_start); y <= (line->draw_wall_end); y++)
	// {
	// 	my_mlx_pixel_put(img, X, y, 0x00FFFF00);
	// }
	// floor (fixed test color)
	for (int y = (line->draw_wall_end + 1); y < WINDOW_HEIGHT; y++)
		my_mlx_pixel_put(img, X, y, game->floor_color);
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
		// ceiling (fixed test color)
		print_tex(game,&line,&img, X);
		//debag
		// print_line(&line,X);
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

	//in loop yobidasiteru
	set_start_vision(game);
	printf("end : set_texture : set_start_vision\n");

	return (0);
}
