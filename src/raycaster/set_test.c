/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 01:00:44 by mkuida            #+#    #+#             */
/*   Updated: 2025/08/19 02:05:27 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub.h"

static int set_map(t_map *map_data)
{
	//not_ptr
    map_data->width = 15;
    map_data->height = 7;
    map_data->player_x = 2;
    map_data->player_y = 3;
    map_data->player_dir = 'N';


	// 元データ（ハードコード）
	const char *src[] = 
	{
		"111111111111111",
		"100000000000001",
		"101111011111101",
		"10N000000000001",
		"101011111110101",
		"100000000000001",
		"111111111111111"
	};

	//map_prep
	map_data->map = malloc((map_data->height) * sizeof(char*));
	if(map_data->map == NULL)
	{
		printf("malloc error\n");
		exit(EXIT_FAILURE);
	}
	for(int y = 0 ; y < (map_data->height) ; y++)
	{
		map_data->map[y] = malloc(sizeof(char) * (map_data->width + 1));
		if(map_data->map[y] == NULL)
		{
			printf("malloc error\n");
			exit(EXIT_FAILURE);
		}
		strncpy(map_data->map[y], src[y], map_data->width);
		map_data->map[y][map_data->width] = '\0';
	}

	// 確認出力
	// for (int y = 0; y < map_data->height; y++)
	// 	printf("%s\n", map_data->map[y]);

	return (0);
}

//1 2 4 8 16 32 64 128
static int set_rgb(int *dest, int red,int green,int blue)
{
	if(red < 0 || red > 255)
		return (1);
	if(green < 0 || green > 255)
		return (1);
	if(blue < 0 || blue > 255)
		return (1);

	*dest = 0;
	*dest += red;
	*dest += (green << 8);
	*dest += (blue << 16);
	return (0);
}


int set_test(t_game *game)
{
	set_map(&(game->map_data));
	//set_texture
	game->north_texture = "./textures/north.xpm";
	game->south_texture = "./textures/south.xpm";
	game->east_texture = "./textures/east.xpm";
	game->west_texture = "./textures/west.xpm";

	if(set_rgb(&(game->floor_color),255,0,0) == 1)
		return (1);
	// printf("floor_color = %d\n",game->floor_color);
	if(set_rgb(&(game->ceiling_color),0,255,0) == 1)
		return (1);
	// printf("ceiling_color = %d\n",game->ceiling_color);
	
	//set minilib
	game->mlx = NULL;
	game->win = NULL;

	game->north_img = NULL;
	game->south_img = NULL;
	game->east_img = NULL;
	game->west_img = NULL;

	//set player
		//位置
	game->player_pos_x = 0;
	game->player_pos_y = 0;
		//向き
	game->player_dir_x = 0;
	game->player_dir_y = 0;
		//視覚幅
	game->player_plane_x = 0;
	game->player_plane_y = 0;
	return (0);
}
