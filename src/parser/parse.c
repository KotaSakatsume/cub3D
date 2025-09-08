/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:02:17 by kotasakatsu       #+#    #+#             */
/*   Updated: 2025/09/08 18:18:11 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// ================= Utility =================

// normalize_map は先ほどの完成版を使用

// マップをターミナルに表示する関数
void	print_map(t_map *map)
{
	int	y;
	int	x;

	if (!map || !map->map)
		return ;
	printf("Map (width: %d, height: %d):\n", map->width, map->height);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (x < (int)strlen(map->map[y]))
				putchar(map->map[y][x]);
			else
				putchar(' ');
			x++;
		}
		putchar('\n');
		y++;
	}
}

static const char	*skip_spaces(const char *s)
{
	while (*s == ' ' || *s == '\t')
		s++;
	return (s);
}

// ================= Map Helper =================

int	is_map_line(char *line)
{
	int	i;

	if (!line || line[0] == '\0')
		return (0);
	i = 0;
	while (line[i] != '\0')
	{
		if (!(line[i] == '1' || line[i] == '0' || line[i] == 'N'
				|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W'
				|| line[i] == ' '))
			return (0);
		i++;
	}
	return (1);
}

void	add_map_line(t_map *map, const char *line)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (map->height + 2));
	if (!new_map)
		error_exit("Malloc failed for map", NULL);
	i = 0;
	while (i < map->height)
	{
		new_map[i] = map->map[i];
		i++;
	}
	new_map[i] = strdup(line);
	if (!new_map[i])
		error_exit("Malloc failed for map line", NULL);
	new_map[i + 1] = NULL;
	free(map->map);
	map->map = new_map;
	map->height++;
}

void	parse_config_line(t_game *game, const char *line)
{
	line = skip_spaces(line);
	if (*line == '\0')
		return ;
	if (strncmp(line, "NO", 2) == 0 && (line[2] == ' ' || line[2] == '\t'))
		parse_texture(game, skip_spaces(line + 2), &game->north_texture);
	else if (strncmp(line, "SO", 2) == 0 && (line[2] == ' ' || line[2] == '\t'))
		parse_texture(game, skip_spaces(line + 2), &game->south_texture);
	else if (strncmp(line, "WE", 2) == 0 && (line[2] == ' ' || line[2] == '\t'))
		parse_texture(game, skip_spaces(line + 2), &game->west_texture);
	else if (strncmp(line, "EA", 2) == 0 && (line[2] == ' ' || line[2] == '\t'))
		parse_texture(game, skip_spaces(line + 2), &game->east_texture);
	else if (*line == 'F' && (line[1] == ' ' || line[1] == '\t'))
		parse_color(game, skip_spaces(line + 1), &game->floor_color);
	else if (*line == 'C' && (line[1] == ' ' || line[1] == '\t'))
		parse_color(game, skip_spaces(line + 1), &game->ceiling_color);
	else if (is_map_line((char *)line))
		add_map_line(&game->map_data, line);
	else
		error_exit("Unknown identifier in config file", game);
}

// ================= Main Parse =================

int	parse_file(t_game *game, char *filename)
{
	char	**file_content;
	int		i;
	int		map_started;
	char	*line;

	// 1. ファイルを読み込み
	file_content = read_file(game, filename);
	if (!file_content)
		return (0);
	// 2. 各行をパース
	i = 0;
	map_started = 0;
	while (file_content[i] != NULL)
	{
		line = file_content[i];
		if (is_map_line(line))
		{
			map_started = 1;
			add_map_line(&game->map_data, line);
		}
		else if (map_started)
		{
			// マップ開始後にマップ判定に引っかからない行は無効
			error_exit("Invalid line after map started", game);
		}
		else
		{
			// マップ開始前は設定行のみ
			parse_config_line(game, line);
		}
		i++;
	}
	// 3. マップの正規化（行幅を揃える）
	normalize_map(&game->map_data);
	// 4. マップのバリデーション（壁で囲まれているか、プレイヤーが1人か）
	validate_map(game);
	set_player_start(game);
	// 5. 確認用出力（任意）
	printf("NO : %s\n", game->north_texture);
	printf("SO : %s\n", game->south_texture);
	printf("WE : %s\n", game->west_texture);
	printf("EA : %s\n", game->east_texture);
	printf("F  : %d\n", game->floor_color);
	printf("C  : %d\n", game->ceiling_color);
	print_map(&game->map_data);
	printf("=====Player position set=====\n");
	printf("X: %d\n", game->map_data.player_x);
	printf("Y: %d\n", game->map_data.player_y);
	printf("Direction: %c\n", game->map_data.player_dir);
	i = 0;
	while (file_content[i] != NULL)
	{
		free(file_content[i]);
		i++;
	}
	free(file_content);
	// 成功
	return (1);
}
