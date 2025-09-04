/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:02:17 by kotasakatsu       #+#    #+#             */
/*   Updated: 2025/09/04 17:51:11 by kosakats         ###   ########.fr       */
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
			// 行が短い場合は空白で埋めて出力
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

static char	*process_line(char *line)
{
	size_t	len;

	len = strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
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

static int	count_players(t_map *map)
{
	int	count;

	int x, y;
	count = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == 'N' || map->map[y][x] == 'S'
				|| map->map[y][x] == 'E' || map->map[y][x] == 'W')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

static void	check_cell(t_map *map, int y, int x, t_game *game)
{
	if (map->map[y][x] == '0' || map->map[y][x] == 'N' || map->map[y][x] == 'S'
		|| map->map[y][x] == 'E' || map->map[y][x] == 'W')
	{
		// 隣接セルが空白ならエラー
		if (y == 0 || y == map->height - 1 || x == 0 || x == map->width - 1
			|| map->map[y - 1][x] == ' ' || map->map[y + 1][x] == ' '
			|| map->map[y][x - 1] == ' ' || map->map[y][x + 1] == ' ')
			error_exit("Map is not enclosed properly", game);
	}
}

void	validate_map(t_game *game)
{
	t_map	*map;

	map = &game->map_data;
	int y, x;
	if (count_players(map) != 1)
		error_exit("Map must have exactly one player", game);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			check_cell(map, y, x, game);
			x++;
		}
		y++;
	}
}

// void	normalize_map(t_map *map)
// {
// 	int		i;
// 	int		max_len;
// 	int		len;
// 	char	*new_line;
// 	int		j;

// 	max_len = 0;
// 	for (i = 0; i < map->height; i++)
// 	{
// 		len = strlen(map->map[i]);
// 		if (len > max_len)
// 			max_len = len;
// 	}
// 	for (i = 0; i < map->height; i++)
// 	{
// 		len = strlen(map->map[i]);
// 		if (len < max_len)
// 		{
// 			new_line = malloc(max_len + 1);
// 			if (!new_line)
// 				error_exit("Malloc failed in normalize_map", NULL);
// 			for (j = 0; j < len; j++)
// 				new_line[j] = map->map[i][j];
// 			for (; j < max_len; j++)
// 				new_line[j] = ' ';
// 			new_line[max_len] = '\0';
// 			free(map->map[i]);
// 			map->map[i] = new_line;
// 		}
// 	}
// 	map->width = max_len;
// }

// ================= File Reading =================

char	**add_line(char **file_content, int *count, int *capacity, char *line)
{
	char	**new_content;
	int		i;
	int		new_capacity;

	if (line == NULL)
	{
		file_content[*count] = NULL;
		return (file_content);
	}
	if (*count >= *capacity)
	{
		new_capacity = (*capacity == 0) ? 10 : (*capacity * 2);
		new_content = malloc(sizeof(char *) * new_capacity);
		if (!new_content)
			return (NULL);
		for (i = 0; i < *count; i++)
			new_content[i] = file_content[i];
		free(file_content);
		file_content = new_content;
		*capacity = new_capacity;
	}
	file_content[*count] = strdup(line);
	if (!file_content[*count])
		return (NULL);
	(*count)++;
	return (file_content);
}

char	**read_file(t_game *game, char *filename)
{
	char	**file_content;
	char	*line;
	int		count;
	int		capacity;
	int		fd;

	file_content = NULL;
	count = 0;
	capacity = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open file\n", game);
	line = get_next_line(fd);
	while (line)
	{
		line = process_line(line);
		file_content = add_line(file_content, &count, &capacity, line);
		if (!file_content)
			error_exit("Malloc failed\n", game);
		free(line);
		line = get_next_line(fd);
	}
	file_content = add_line(file_content, &count, &capacity, NULL);
	if (!file_content)
		error_exit("Malloc failed\n", game);
	close(fd);
	return (file_content);
}

// ================= Config Parsing =================

void	parse_texture(t_game *game, const char *path, char **texture_path)
{
	int	fd;

	if (*texture_path != NULL)
		error_exit("Duplicate texture definition", game);
	if (!path || *path == '\0')
		error_exit("Missing texture path", game);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_exit("Texture file not found", game);
	close(fd);
	*texture_path = strdup(path);
	if (!*texture_path)
		error_exit("Malloc failed for texture path", game);
}

void	parse_color(t_game *game, const char *color_str, int *color)
{
	char	**rgb;

	int r, g, b, i;
	if (*color != -1)
		error_exit("Duplicate color definition", game);
	rgb = ft_split(color_str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		error_exit("Invalid color format", game);
	r = atoi(rgb[0]);
	g = atoi(rgb[1]);
	b = atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error_exit("Color values out of range", game);
	*color = (r << 16) | (g << 8) | b;
	i = 0;
	while (rgb[i])
	{
		free(rgb[i]);
		i++;
	}
	free(rgb);
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

// マップの行幅を揃えて正方形っぽくする関数
void	normalize_map(t_map *map)
{
	int		i;
	int		max_len;
	int		j;
	int		len;
	char	*new_line;

	// 1. 最大幅を求める
	max_len = 0;
	i = 0;
	while (map->map[i] != NULL)
	{
		len = strlen(map->map[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	map->width = max_len;
	// 2. 各行の幅を揃える（足りない部分は空白で埋める）
	i = 0;
	while (map->map[i] != NULL)
	{
		len = strlen(map->map[i]);
		if (len < max_len)
		{
			new_line = malloc(sizeof(char) * (max_len + 1));
			if (!new_line)
				error_exit("Malloc failed in normalize_map", NULL);
			j = 0;
			while (j < len)
			{
				new_line[j] = map->map[i][j];
				j++;
			}
			while (j < max_len)
			{
				new_line[j] = ' ';
				j++;
			}
			new_line[j] = '\0';
			free(map->map[i]);
			map->map[i] = new_line;
		}
		i++;
	}
	map->height = i;
}

void	set_player_start(t_game *game)
{
	int		y;
	int		x;
	int		found;
	char	c;

	found = 0;
	y = 0;
	while (y < game->map_data.height)
	{
		x = 0;
		while (x < game->map_data.width)
		{
			c = game->map_data.map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (found)
					error_exit("Multiple player positions found", game);
				game->map_data.player_x = x;
				game->map_data.player_y = y;
				game->map_data.player_dir = c;
				game->map_data.map[y][x] = '0';
				found = 1;
			}
			x++;
		}
		y++;
	}
	if (!found)
		error_exit("No player position found", game);
	printf("Player start: x=%d, y=%d, dir=%c\n", game->map_data.player_x,
		game->map_data.player_y, game->map_data.player_dir);
}

// ================= Main Parse =================

int	parse_file(t_game *game, char *filename)
{
	char	**file_content;
	int		i;

	// 1. ファイルを読み込み
	file_content = read_file(game, filename);
	if (!file_content)
		return (0);
	// 2. 各行をパース
	i = 0;
	while (file_content[i] != NULL)
	{
		if (is_map_line(file_content[i]))
			add_map_line(&game->map_data, file_content[i]);
		else
			parse_config_line(game, file_content[i]);
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
