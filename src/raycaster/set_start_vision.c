/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_start_vision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 18:00:46 by mkuida            #+#    #+#             */
/*   Updated: 2025/09/10 19:43:20 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	print_wall_color(t_game *game, t_linedraw *line, t_img *img, int X)
{
	t_img	*original_data;
	int		original_x;
	int		wall_color;
	double	y_raito;
	int		original_y;

	if (line->wall_side == 'w')
	{
		original_data = &game->west_img;
		original_x = (1.0 - (line->hit_point)) * (original_data->width);
	}
	else if (line->wall_side == 'n')
	{
		original_data = &game->north_img;
		original_x = (line->hit_point) * (original_data->width);
	}
	else if (line->wall_side == 'e')
	{
		original_data = &game->east_img;
		original_x = (line->hit_point) * (original_data->width);
	}
	else if (line->wall_side == 's')
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
	//printf("hit_point = %f : original_width = %d : original_x =%d\n",
	//	line->hit_point, original_data->width, original_x);
	for (int y = (line->draw_wall_start); y <= (line->draw_wall_end); y++)
	{
		y_raito = ((double)(y - (line->draw_wall_start)) / (line->wall_height));
		// printf("y_raito = %f\n",y_raito);
		original_y = (original_data->height) * (y_raito);
		// printf("original_x = %d : original_y = %d\n",original_x,original_y);
		wall_color = my_mlx_pixel_get(original_data, original_x, original_y);
		my_mlx_pixel_put(img, X, y, wall_color);
	}
}

static void	print_tex(t_game *game, t_linedraw *line, t_img *img, int X)
{
	// ceil
	for (int y = 0; y < line->draw_wall_start; y++)
		my_mlx_pixel_put(img, X, y, game->ceiling_color);
	// wall
	print_wall_color(game, line, img, X);
	// for (int y = (line->draw_wall_start); y <= (line->draw_wall_end); y++)
	// {
	// 	my_mlx_pixel_put(img, X, y, 0x00FFFF00);
	// }
	// floor (fixed test color)
	for (int y = (line->draw_wall_end + 1); y < WINDOW_HEIGHT; y++)
		my_mlx_pixel_put(img, X, y, game->floor_color);
}

void	set_start_vision(t_game *game)
{
	static bool first = true;
	int			X;
	t_linedraw	line;

	X = 0;
	if(game->screen.mlx_img == NULL)
	{
		game->screen.mlx_img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
		game->screen.addr = mlx_get_data_addr(game->screen.mlx_img, &game->screen.bpp, &game->screen.line_len,
				&game->screen.endian);
	}
	while (X < WINDOW_WIDTH)
	{
		init_line(&line, X, game);
		set_line_by_dda(game, &line);
		// ceiling (fixed test color)
		print_tex(game, &line, &(game->screen), X);
		// debag
		X++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->screen.mlx_img, 0, 0);
	// mlx_destroy_image(game->mlx,img.mlx_img);
}
