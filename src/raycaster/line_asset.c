/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_asset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 10:41:14 by mkuida            #+#    #+#             */
/*   Updated: 2025/08/27 10:41:14 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static double set_delta(double ray)
{
	if(ray == 0)
		return (INFINITY);
	else
		return(fabs(1/ray));
}

static bool check_out_map(t_map *map, int X, int Y)
{
	if(X < 0 || Y < 0)
		return (true);
	if(X >= (map->width) || Y >= (map->height))
		return (true);
	return(false);
}

static bool check_hit_wall(t_map *map, int X, int Y)
{
	if(map->map[Y][X] == '1')
		return (true);
	return (false);
}

void init_line(t_line_draw *line, int X, t_game *game)
{
	//for situation
	line->cameraX = ((2.0 * X) / (WINDOW_WIDTH-1) - 1.0); // 1~-1の倍率
	
	line->rayX = game->player_dir_x + ((game->player_plane_x) * (line->cameraX));
	line->rayY = game->player_dir_y + ((game->player_plane_y) * (line->cameraX));
	line->deltaX = set_delta(line->rayX);
	line->deltaY = set_delta(line->rayY);

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

void set_line_by_DDA(t_game *game, t_line_draw *line)
{
	//set_delt
	// double deltaX = set_delta((line->rayX));
	// double deltaY = set_delta((line->rayY));;
	
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
		nextXtime = ((game->player_pos_x) - tileX) * (line->deltaX);
	}
	else
	{
		stepX = 1;
		//nextXtime = ((game->player_pos_x) + 1 - tileX) * deltaX;
		nextXtime = ((tileX + 1) - (game->player_pos_x)) * (line->deltaX);
	}

	if(line->rayY < 0)
	{
		stepY = -1;
		nextYtime = ((game->player_pos_y) - tileY) * (line->deltaY);
	}
	else
	{
		stepY = 1;
		//nextYtime = ((game->player_pos_y) + 1 - tileY) * deltaY;
		nextYtime = ((tileY + 1) - (game->player_pos_y)) * (line->deltaY);
	}

	//DDA
	int hit_side = -1;
	int hit = 0;
	while(hit == 0)
	{
		if(nextXtime < nextYtime)
		{
			nextXtime += (line->deltaX);
			tileX += stepX;
			hit_side = 0;
		}
		else
		{
			nextYtime += (line->deltaY);
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