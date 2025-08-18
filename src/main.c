/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:03:06 by kotasakatsu       #+#    #+#             */
/*   Updated: 2025/08/18 17:20:51 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// void error_exit(char *message)
// {
//     write(2, "Error\n", 6);
//     if (message)
//         write(2, message, strlen(message));
//     exit(1);
// }

// int main(int argc, char **argv)
// {
//     t_game  game;

//     // 1. 引数のチェック
//     if (argc != 2)
//         return (error_exit("Usage: ./cub3d <map.cub>"), 1);
//     if (!check_extension(argv[1], ".cub"))
//         return (error_exit("File must have .cub extension"), 1);

//     // 2. パース処理の開始
//     if (!parse_file(&game, argv[1]))
//         return (1); // parse_file内でエラーメッセージは出力済み

//     // 3. ゲームの初期化と実行
//     init_game(&game);
//     run_game(&game);
    
//     return (0);
// }


//以下、mkuidaの記述部分

//1 2 4 8 16 32 64 128
int set_rgb(int *dest, int red,int green,int blue)
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
	//set_texture
	game->north_texture = "./tesxtures/north.xpm";
	game->south_texture = "./tesxtures/south.xpm";
	game->east_texture = "./tesxtures/east.xpm";
	game->west_texture = "./tesxtures/west.xpm";

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

int check_texture(t_game *game)
{
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

int main()
{
	t_game game;
	
	//test条件設定
	if(set_test(&game) == 1)
	{
		printf("error : set_test\n");
		return (1);
	}

	//xpm形式のtexture確認＆読み込み
	if(check_texture(&game) == 1)
	{
		printf("error : check_texture\n");
		return (1);
	}

	//hookの設定
	set_mlx_hook(&game);

	//画面描画ループ
	mlx_loop(game.mlx);
	return (0);
}