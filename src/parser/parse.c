/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:02:17 by kotasakatsu       #+#    #+#             */
/*   Updated: 2025/09/10 14:37:01 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

	// 新しい配列を確保
	new_map = malloc(sizeof(char *) * (map->height + 2));
	if (!new_map)
		error_exit("Malloc failed for map", NULL);
	// 既存のポインタをコピー（文字列自体はコピーしない）
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

// void	free_file_content(char **file_content)
// {
// 	int	i;

// 	if (!file_content)
// 		return ;
// 	i = 0;
// 	while (file_content[i])
// 	{
// 		free(file_content[i]);
// 		i++;
// 	}
// 	free(file_content);
// }

int	parse_file(t_game *game, char *filename)
{
	int		i;
	int		map_started;
	char	*line;

	// char	**file_content;
	game->file_content = read_file(game, filename);
	if (!game->file_content)
		return (0);
	i = 0;
	map_started = 0;
	while (game->file_content[i] != NULL)
	{
		line = game->file_content[i];
		if (is_map_line(line))
		{
			map_started = 1;
			add_map_line(&game->map_data, line);
		}
		else if (map_started)
		{
			// free_file_content(game->file_content);
			error_exit("Invalid line after map started", game);
		}
		else
			parse_config_line(game, line);
		i++;
	}
	if (game->map_data.height == 0 || !game->map_data.map)
		error_exit("Map is empty", game);
	normalize_map(&game->map_data);
	validate_map(game);
	set_player_start(game);
	// printf("NO : %s\n", game->north_texture);
	// printf("SO : %s\n", game->south_texture);
	// printf("WE : %s\n", game->west_texture);
	// printf("EA : %s\n", game->east_texture);
	// printf("F  : %d\n", game->floor_color);
	// printf("C  : %d\n", game->ceiling_color);
	// print_map(&game->map_data);
	// printf("=====Player position set=====\n");
	// printf("X: %d\n", game->map_data.player_x);
	// printf("Y: %d\n", game->map_data.player_y);
	// printf("Direction: %c\n", game->map_data.player_dir);
	if (game->floor_color == -1 || game->ceiling_color == -1)
	{
		// free_file_content(game->file_content);
		error_exit("Floor or ceiling color not set", game);
	}
	free_file_content(game->file_content);
	return (1);
}

/*	// printf("NO : %s\n", game->north_texture);
	// printf("SO : %s\n", game->south_texture);
	// printf("WE : %s\n", game->west_texture);
	// printf("EA : %s\n", game->east_texture);
	// printf("F  : %d\n", game->floor_color);
	// printf("C  : %d\n", game->ceiling_color);
	// print_map(&game->map_data);
	// printf("=====Player position set=====\n");
	// printf("X: %d\n", game->map_data.player_x);
	// printf("Y: %d\n", game->map_data.player_y);
	// printf("Direction: %c\n", game->map_data.player_dir);*/