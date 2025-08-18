/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 00:08:36 by mkuida            #+#    #+#             */
/*   Updated: 2025/08/19 00:45:16 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	start_mlx(t_game *game)
{
	//init_mlx
	game->mlx = mlx_init();
	if(game->mlx == NULL)
	{
		perror("mlx_init");
		//exitでいいか確認
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
		printf("mlx_xpm_file_to_image (xpm_path = %s)\n",xpm_path);
		exit(EXIT_FAILURE);
	}
	full_data.addr = mlx_get_data_addr(full_data.mlx_img, &(full_data.bpp), &(full_data.line_len), &(full_data.endian));
	if(full_data.addr == NULL)
	{
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


int set_texture(t_game *game)
{
	start_mlx(game);
	set_imgs_data(game);
	return (0);
}