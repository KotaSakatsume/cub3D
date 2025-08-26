/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 00:08:36 by mkuida            #+#    #+#             */
/*   Updated: 2025/08/26 00:58:19 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	start_mlx(t_game *game)
{
	if(WINDOW_WIDTH < 1)
	{
		perror("mlx_init : check your WINDOW_WIDTH");
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

static int 	set_img_data(t_game *game, char *xpm_path)
{
	t_img	full_data;
	
	full_data.mlx_img = mlx_xpm_file_to_image(game->mlx, xpm_path, &(full_data.width), &(full_data.height));
	if(full_data.mlx_img == NULL)
	{
		//exitなので修正必要
		printf("mlx_xpm_file_to_image (xpm_path = %s)\n",xpm_path);
		exit(EXIT_FAILURE);
	}

	full_data.addr = mlx_get_data_addr(full_data.mlx_img, &(full_data.bpp), &(full_data.line_len), &(full_data.endian));
	if(full_data.addr == NULL)
	{
		//exitなので修正必要
		printf("mlx_get_data_addr\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}

static int	set_imgs_data(t_game *game)
{
	set_img_data(game,game->north_texture);
	set_img_data(game,game->east_texture);
	set_img_data(game,game->west_texture);
	set_img_data(game,game->south_texture);
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


void set_player(t_game *game)
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

bool check_out_map(t_map *map, int X , int Y)
{
	if(X < 0 || Y < 0)
		return true;
	if(X >= (map->width) || Y >= (map->height))
		return true;
	return(false);
}

bool check_hit_wall(t_map *map, int X, int Y)
{
	if(map->map[Y][X] == '1')
		return true;
	return false;
}

void DDA(t_game *game, t_line_draw *line)
{
	//set_delt
	double deltaX;
	double deltaY;

	if(line->rayX == 0)
		deltaX = INFINITY;
	else
		deltaX = fabs(1/(line->rayX));
	
	if((line->rayY) == 0)
		deltaY = INFINITY;
	else
		deltaY = fabs(1/(line->rayY));
	
	//set_step
	int stepX;
	int stepY;

	double nextXtime;
	double nextYtime;

	int tileX = (int)(game->player_pos_x);
	int tileY = (int)(game->player_pos_y);

	if(line->rayX < 0)
	{
		stepX = -1;
		nextXtime = ((game->player_pos_x) - tileX) * deltaX;
	}
	else
	{
		stepX = 1;
		//nextXtime = ((game->player_pos_x) + 1 - tileX) * deltaX;
		nextXtime = ((tileX + 1) - (game->player_pos_x)) * deltaX;
	}

	if(line->rayY < 0)
	{
		stepY = -1;
		nextYtime = ((game->player_pos_y) - tileY) * deltaY;
	}
	else
	{
		stepY = 1;
		//nextYtime = ((game->player_pos_y) + 1 - tileY) * deltaY;
		nextYtime = ((tileY + 1) - (game->player_pos_y)) * deltaY;
	}

	//DDA
	int hit_side = -1;
	int hit = 0;
	while(hit == 0)
	{
		if(nextXtime < nextYtime)
		{
			nextXtime += deltaX;
			tileX += stepX;
			hit_side = 0;
		}
		else
		{
			nextYtime += deltaY;
			tileY += stepY;
			hit_side = 1;
		}
		if(check_out_map(&(game->map_data), tileX, tileY) == true)
		{
			printf("out map\n");
			printf("tileX = %d , tileY = %d\n",tileX,tileY);
			exit(1);
		}
		if(check_hit_wall(&(game->map_data), tileX, tileY) == true)
			hit = 1;
	}

	//kyori & kabe_no_hougaku
	if(hit_side == 0)
	{
		(line->distinct) = (tileX - (game->player_pos_x)) + ((1- stepX) / 2);
		(line->distinct) = (line->distinct) / (line->rayX); //gyogann
		if(line->rayX > 0)
			(line -> wall_side) = 'w';
		else
			(line -> wall_side) = 'e';
	}
	else
	{
		(line->distinct) = (tileY - (game->player_pos_y)) + ((1- stepY) / 2);
		(line->distinct) = (line->distinct) / (line->rayY); //gyogann
		if(line->rayY > 0)
			(line -> wall_side) = 'n';
		else
			(line -> wall_side) = 's';
	}
	//壁の相対位置（０～１）
	if(hit_side == 0)
		(line->hit_point) = (game->player_pos_y) + ((line->distinct)*(line->rayY));
	else
		(line->hit_point) = (game->player_pos_x) + ((line->distinct)*(line->rayX));
	(line->hit_point) = floor((line->hit_point));

	//壁の大きさ
	if((line->distinct) == 0)
		(line->wall_height) = WINDOW_HEIGHT;
	else
		(line->wall_height) = (WINDOW_HEIGHT / (line->distinct));

	//drawstart~end
	(line->draw_wall_start) = (-(line->wall_height) / 2) + (WINDOW_HEIGHT/2);
	if((line->draw_wall_start) < 0)
		(line->draw_wall_start) = 0;
	(line->draw_wall_end) = ((line->wall_height) / 2) + (WINDOW_HEIGHT/2);
		if((line->draw_wall_end) >= WINDOW_HEIGHT)
		(line->draw_wall_end) = WINDOW_HEIGHT - 1;

	//hit
	(line->hit_X) = tileX;
	(line->hit_Y) = tileY;

	return;
}

void init_line(t_line_draw *line, int X, t_game *game)
{

	//for situation
	line->cameraX = ((2.0 * X) / (WINDOW_WIDTH-1) - 1.0); // 1~-1の倍率
	line->rayX = game->player_dir_x + ((game->player_plane_x) * (line->cameraX));
	line->rayY = game->player_dir_y + ((game->player_plane_y) * (line->cameraX));

	//for ans
	line->draw_wall_start = -1;
	line->draw_wall_end = -1;
	line->wall_height = -1;

	line->wall_side = ' ';

	line->hit_X = -1;
	line->hit_Y = -1;

	line->distinct = -1;
	
	line->hit_point = -1;
}

// void set_pixcel(t_game *game)
// {
	
// }
void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void print_line(t_line_draw *line, int X)
{
	printf("print line start: X = %d\n",X);
	//初期条件
	printf("rayX = %f : rayY = %f : camera = %f\n",line->rayX,line->rayY,line->cameraX);


	//結果
	printf("draw_wall_start = %d : draw_wall_end = %d : wall_height = %d\n",line->draw_wall_start,line->draw_wall_end,line->wall_height);


	printf("wall_side = %c\n",line->wall_side);


	
	printf("hit_x = %d : hit_y = %d\n",line->hit_X,line->hit_Y);


	printf("distinct = %f\n",line->distinct);


	printf("hit_point = %f\n",line->hit_point);

	printf("print line end: X = %d\n",X);
}

void set_start_vision(t_game *game)
{
	int X = 0;
	t_line_draw line;
	t_img img;
	img.mlx_img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.mlx_img, &img.bpp, &img.line_len, &img.endian);

	printf("①\n");

	while(X < WINDOW_WIDTH)
	{
		printf("A\n");
		init_line(&line, X, game);
		printf("B\n");
		DDA(game,&line);
		printf("C\n");
		// set_pixcel(game);
		// test
		// ceiling (fixed test color)
		for (int y = 0; y < line.draw_wall_start; y++)
		{
			//my_mlx_pixel_put(&img, X, y, game->ceiling_color);
			my_mlx_pixel_put(&img, X, y, 0x222222);
		}
		// wall
		for (int y = (line.draw_wall_start); y <= (line.draw_wall_end); y++)
		{
			my_mlx_pixel_put(&img, X, y, 0xFF0000);
		}
		// floor (fixed test color)
		for (int y = (line.draw_wall_end + 1); y < WINDOW_HEIGHT; y++)
		{
			//my_mlx_pixel_put(&img, X, y, game->floor_color);
			my_mlx_pixel_put(&img, X, y, 0x444444);
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

	set_imgs_data(game);
	printf("end : set_texture : set_imgs_data\n");

	set_player(game);
	printf("end : set_texture : set_player\n");

	set_start_vision(game);
	printf("end : set_texture : set_start_vision\n");

	return (0);
}
