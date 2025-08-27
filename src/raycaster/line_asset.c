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

static void set_distinct_and_wallside(t_game *game, t_line_draw *line)
{
	if((line->hit_side) == 0)
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
}

static void set_hitpoint(t_game *game, t_line_draw *line)
{
	if((line->hit_side) == 0)
		(line->hit_point) = (game->player_pos_y) + ((line->distinct)*(line->rayY));
	else
		(line->hit_point) = (game->player_pos_x) + ((line->distinct)*(line->rayX));
	(line->hit_point) = floor((line->hit_point));
}

static void set_draw_wall_info(t_line_draw *line)
{
	(line->draw_wall_start) = (-(line->wall_height) / 2) + (WINDOW_HEIGHT/2);
	if((line->draw_wall_start) < 0)
		(line->draw_wall_start) = 0;
	(line->draw_wall_end) = ((line->wall_height) / 2) + (WINDOW_HEIGHT/2);
	if((line->draw_wall_end) >= WINDOW_HEIGHT)
		(line->draw_wall_end) = WINDOW_HEIGHT - 1;
}

static void set_line_param(t_game *game, t_line_draw *line)
{
	set_distinct_and_wallside(game, line);
	set_hitpoint(game, line);
	if((line->distinct) == 0)
		(line->wall_height) = WINDOW_HEIGHT;
	else
		(line->wall_height) = (WINDOW_HEIGHT / (line->distinct));
	set_draw_wall_info(line);
	(line->hit_X) = (line->tileX);
	(line->hit_Y) = (line->tileY);
}

void set_line_by_DDA(t_game *game, t_line_draw *line)
{	
	DDA(line,game);
	set_line_param(game,line);
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
