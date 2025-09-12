/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 00:08:36 by mkuida            #+#    #+#             */
/*   Updated: 2025/09/12 18:10:05 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	start_mlx(t_game *game)
{
	if (WINDOW_WIDTH < WINDOW_MIN_WIDTH || WINDOW_HEIGHT < WINDOW_MIN_HEIGHT)
	{
		ft_printf("Error\n");
		ft_printf("start_mlx : WINDOW SIZE invalid\n");
		return (1);
	}
	game->mlx = mlx_init();
	if (game->mlx == NULL)
	{
		ft_printf("Error\n");
		ft_printf("start_mlx : mlx_init error\n");
		return (1);
	}
	return (0);
}

static void	set_pp(t_game *game)
{
	double	player_plane_length;

	player_plane_length = tan(M_PI * (FOV / 2) / 180);
	game->player_plane_x = -(game->player_dir_y) * player_plane_length;
	game->player_plane_y = (game->player_dir_x) * player_plane_length;
}

static void	set_start_player_posi(t_game *game)
{
	game->player_pos_x = (game->map_data.player_x) + 0.5;
	game->player_pos_y = (game->map_data.player_y) + 0.5;
	if (game->map_data.player_dir == 'N')
		game->player_dir_y = -1;
	else if (game->map_data.player_dir == 'E')
		game->player_dir_x = 1;
	else if (game->map_data.player_dir == 'W')
		game->player_dir_x = -1;
	else if (game->map_data.player_dir == 'S')
		game->player_dir_y = 1;
	else
	{
		ft_printf("Error\nset_player\n");
		exit(1);
	}
	set_pp(game);
}

static void	destroy_inputed_image(t_game *game)
{
	mlx_destroy_image(game->mlx, game->north_img.mlx_img);
	mlx_destroy_image(game->mlx, game->east_img.mlx_img);
	mlx_destroy_image(game->mlx, game->west_img.mlx_img);
	mlx_destroy_image(game->mlx, game->south_img.mlx_img);
}

int	set_texture(t_game *game)
{
	if (start_mlx(game) == 1)
		return (1);
	if (set_mlx_imgs_wall_data(game) == 1)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		return (1);
	}
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (game->win == NULL)
	{
		ft_printf("Error\n");
		ft_printf("cant open wall data\n");
		destroy_inputed_image(game);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		return (1);
	}
	set_start_player_posi(game);
	set_start_vision(game);
	return (0);
}
