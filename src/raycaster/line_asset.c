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

void set_line_by_DDA(t_game *game, t_line_draw *line)
{	
	//DDA
	int hit_side = -1;
	int hit = 0;
	while(hit == 0)
	{
		if((line->nextXtime) < (line->nextYtime))
		{
			(line->nextXtime) += (line->deltaX);
			(line->tileX) += (line->stepX);
			hit_side = 0;
		}
		else
		{
			(line->nextYtime) += (line->deltaY);
			(line->tileY) += (line->stepY);
			hit_side = 1;
		}
		if(check_out_map(&(game->map_data), (line->tileX), (line->tileY)) == true)
		{
			printf("out map\n");
			printf("(line->tileX) = %d , (line->tileY) = %d\n",(line->tileX),(line->tileY));
			exit(1);
		}
		if(check_hit_wall(&(game->map_data), (line->tileX), (line->tileY)) == true)
			hit = 1;
	}

	//kyori & kabe_no_hougaku
	if(hit_side == 0)
	{
		(line->distinct) = ((line->tileX) - (game->player_pos_x)) + ((1- (line->stepX)) / 2);
		(line->distinct) = (line->distinct) / (line->rayX); //gyogann
		if(line->rayX > 0)
			(line -> wall_side) = 'w';
		else
			(line -> wall_side) = 'e';
	}
	else
	{
		(line->distinct) = ((line->tileY) - (game->player_pos_y)) + ((1- (line->stepY)) / 2);
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
	(line->hit_X) = (line->tileX);
	(line->hit_Y) = (line->tileY);

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
