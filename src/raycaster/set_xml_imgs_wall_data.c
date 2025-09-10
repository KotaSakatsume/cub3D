/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_imgs_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 10:13:34 by mkuida            #+#    #+#             */
/*   Updated: 2025/08/27 10:13:34 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int 	set_img_data(t_game *game, char *xpm_path, t_img *full_data)
{	
	if(xpm_path == NULL)
		return (1);
	full_data->mlx_img = mlx_xpm_file_to_image(game->mlx, xpm_path, &(full_data->width), &(full_data->height));
	if(full_data->mlx_img == NULL)
	{
		ft_printf("set_img_data : can't change mlx_xpm_file_to_image (xpm_path = %s)\n",xpm_path);
		return (1);
	}

	full_data->addr = mlx_get_data_addr(full_data->mlx_img, &(full_data->bpp), &(full_data->line_len), &(full_data->endian));
	if(full_data->addr == NULL)
	{
		perror("set_img_data : mlx_get_data_addr\n");
		mlx_destroy_image(game->mlx, full_data);
		return (1);
	}
	return (0);
}

int set_xml_imgs_wall_data(t_game *game)
{
	if(set_img_data(game, game->north_texture, &game->north_img) == 1)
		return (1);
	if(set_img_data(game, game->east_texture, &game->east_img) == 1)
	{
		mlx_destroy_image(game->mlx, game->north_img.mlx_img);
		return (1);
	}
	if(set_img_data(game, game->west_texture, &game->west_img) == 1)
	{
		mlx_destroy_image(game->mlx, game->north_img.mlx_img);
		mlx_destroy_image(game->mlx, game->east_img.mlx_img);
		return (1);
	}
	if(set_img_data(game, game->south_texture, &game->south_img) == 1)
	{
		mlx_destroy_image(game->mlx, game->north_img.mlx_img);
		mlx_destroy_image(game->mlx, game->east_img.mlx_img);
		mlx_destroy_image(game->mlx, game->west_img.mlx_img);
		return (1);
	}
	return (0);
}
