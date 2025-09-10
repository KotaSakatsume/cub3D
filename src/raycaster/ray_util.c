/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 14:26:49 by mkuida            #+#    #+#             */
/*   Updated: 2025/09/10 19:26:32 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	max(int x, int y)
{
	if (x >= y)
		return (x);
	else
		return (y);
}

int	min(int x, int y)
{
	if (x >= y)
		return (y);
	else
		return (x);
}

void	free_game(t_game *game)
{
	int i;

	i = 0;
	free(game->north_texture);
	free(game->south_texture);
	free(game->east_texture);
	free(game->west_texture);
	while(i < (game->map_data.height))
	{
		free(game->map_data.map[i]);
		i++;
	}
	free(game->map_data.map);
	free(game);
}

void	destroy_all_image(t_game *game)
{
	mlx_destroy_image(game->mlx, game->north_img.mlx_img);
	mlx_destroy_image(game->mlx, game->east_img.mlx_img);
	mlx_destroy_image(game->mlx, game->west_img.mlx_img);
	mlx_destroy_image(game->mlx, game->south_img.mlx_img);
	mlx_destroy_image(game->mlx, game->screen.mlx_img);
}

void	print_line(t_linedraw *line, int X)
{
	ft_printf("print line start: X = %d\n", X);
	ft_printf("rayX = %f : rayY = %f : camera = %f\n", line->rayX, line->rayY,
		line->cameraX);
	ft_printf("draw_wall_start = %d : draw_wall_end = %d : wall_height = %d\n",
		line->draw_wall_start, line->draw_wall_end, line->wall_height);
	ft_printf("wall_side = %c\n", line->wall_side);
	ft_printf("hit_x = %d : hit_y = %d\n", line->hit_X, line->hit_Y);
	ft_printf("distinct = %f\n", line->distinct);
	ft_printf("hit_point = %f\n", line->hit_point);
	ft_printf("print line end: X = %d\n", X);
}
