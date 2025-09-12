/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 17:56:32 by kotasakatsu       #+#    #+#             */
/*   Updated: 2025/09/12 18:07:18 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_map(t_map *map)
{
	map->map = NULL;
	map->width = 0;
	map->height = 0;
	map->player_x = -1;
	map->player_y = -1;
	map->player_dir = 'N';
}

static void	init_t_img(t_img *img)
{
	img->mlx_img = NULL;
	img->addr = NULL;
	img->width = 0;
	img->height = 0;
	img->bpp = 0;
	img->line_len = 0;
	img->endian = 0;
}

void	init_game(t_game *game)
{
	game->player_pos_x = 0.0;
	game->player_pos_y = 0.0;
	game->player_dir_x = 0.0;
	game->player_dir_y = 0.0;
	game->player_plane_x = 0.0;
	game->player_plane_y = 0.66;
	game->north_texture = NULL;
	game->south_texture = NULL;
	game->east_texture = NULL;
	game->west_texture = NULL;
	game->floor_color = -1;
	game->ceiling_color = -1;
	game->mlx = NULL;
	game->win = NULL;
	game->file_content = NULL;
	init_map(&game->map_data);
	init_t_img(&game->north_img);
	init_t_img(&game->east_img);
	init_t_img(&game->west_img);
	init_t_img(&game->south_img);
	init_t_img(&game->screen);
}
