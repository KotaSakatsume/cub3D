/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:03:06 by kotasakatsu       #+#    #+#             */
/*   Updated: 2025/09/12 17:08:26 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_file_content(char **file_content)
{
	int	i;

	if (!file_content)
		return ;
	i = 0;
	while (file_content[i])
	{
		free(file_content[i]);
		i++;
	}
	free(file_content);
}

void	free_map(t_map *map)
{
	int	i;

	if (!map || !map->map)
		return ;
	i = 0;
	while (map->map[i])
	{
		free(map->map[i]);
		i++;
	}
	free(map->map);
	map->map = NULL;
}

// textures の解放
void	free_textures(t_game *game)
{
	if (!game)
		return ;
	free(game->north_texture);
	free(game->south_texture);
	free(game->west_texture);
	free(game->east_texture);
	game->north_texture = NULL;
	game->south_texture = NULL;
	game->west_texture = NULL;
	game->east_texture = NULL;
}

// F/C 色は int などの場合解放不要だが、別途 malloc していた場合は free を追加

// 完全版 error_exit
void	error_exit(char *message, t_game *game)
{
	write(2, "Error\n", 6);
	if (message)
		write(2, message, strlen(message));
	if (game)
	{
		free_file_content(game->file_content);
		free_map(&game->map_data);
		free_textures(game);
		free(game);
	}
	exit(1);
}

int	check_extension(const char *filename, const char *extension)
{
	size_t	len;

	if (!filename)
		return (0);
	len = strlen(filename);
	if (len < 4 || strncmp(filename + len - 4, extension, 5))
		return (0);
	return (1);
}

#include <stdio.h>

void	printf_map(t_map *map)
{
	int	y;

	y = 0;
	printf("Map (width=%d, height=%d):\n", map->width, map->height);
	while (y < map->height)
	{
		printf("%s\n", map->map[y]);
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (write(2, "Memory allocation failed\n", 25));
	if (argc != 2)
		return (free(game), write(2, "Usage: ./cub3d <map.cub>\n", 25), 1);
	if (!check_extension(argv[1], ".cub"))
		return (free(game), write(2, "File must have .cub extension\n", 30));
	init_game(game);
	if (!parse_file(game, argv[1]))
		return (1); // parse_file内でエラーメッセージは出力済み
	// ------------------------------
	// デバッグ表示
	// ------------------------------
	printf("=== NEWS (Textures) ===\n");
	printf("North: %s\n", game->north_texture);
	printf("South: %s\n", game->south_texture);
	printf("East:  %s\n", game->east_texture);
	printf("West:  %s\n", game->west_texture);
	printf("\n=== FC (Floor / Ceiling) ===\n");
	printf("Floor:   %d\n", game->floor_color);
	printf("Ceiling: %d\n", game->ceiling_color);
	printf("\n=== MAP ===\n");
	printf_map(&game->map_data);
	// // ------------------------------
	// // メモリ解放
	// // ------------------------------
	// free(game->north_texture);
	// free(game->south_texture);
	// free(game->east_texture);
	// free(game->west_texture);
	// // map_data 内の各行も free する
	// for (int i = 0; i < game->map_data.height; i++)
	// 	free(game->map_data.map[i]);
	// free(game->map_data.map);
	// free(game);
	if (set_texture(game) == 1)
	{
		free_game(game);
		return (1);
	}
	// hookの設定
	set_mlx_hook(game);
	//画面描画ループ
	mlx_loop(game->mlx);
	return (0);
}
