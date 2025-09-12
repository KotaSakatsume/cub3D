/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:02:17 by kotasakatsu       #+#    #+#             */
/*   Updated: 2025/09/12 13:48:07 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
			if (x < (int)ft_strlen(map->map[y]))
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

	new_map = malloc(sizeof(char *) * (map->height + 2));
	if (!new_map)
		error_exit("Malloc failed for map", NULL);
	i = 0;
	while (i < map->height)
	{
		new_map[i] = map->map[i];
		i++;
	}
	new_map[i] = ft_strdup(line);
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
	if (ft_strncmp(line, "NO", 2) == 0 && (line[2] == ' ' || line[2] == '\t'))
		parse_texture(game, skip_spaces(line + 2), &game->north_texture);
	else if (ft_strncmp(line, "SO", 2) == 0 && (line[2] == ' '
			|| line[2] == '\t'))
		parse_texture(game, skip_spaces(line + 2), &game->south_texture);
	else if (ft_strncmp(line, "WE", 2) == 0 && (line[2] == ' '
			|| line[2] == '\t'))
		parse_texture(game, skip_spaces(line + 2), &game->west_texture);
	else if (ft_strncmp(line, "EA", 2) == 0 && (line[2] == ' '
			|| line[2] == '\t'))
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

static int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

static void	process_map_line(t_game *game, char *line, int *map_started,
		int *map_ended)
{
	if (*map_ended)
		error_exit("Invalid line after map ended", game);
	*map_started = 1;
	add_map_line(&game->map_data, line);
}

static void	process_line(t_game *game, char *line, int *map_started,
		int *map_ended)
{
	if (is_empty_line(line))
	{
		if (*map_started && !*map_ended)
			*map_ended = 1;
		return ;
	}
	if (is_map_line(line))
		process_map_line(game, line, map_started, map_ended);
	else if (!*map_started)
		parse_config_line(game, line);
	else
		error_exit("Invalid line after map started", game);
}

static void	parse_lines(t_game *game)
{
	int	i;
	int	map_started;
	int	map_ended;

	map_started = 0;
	map_ended = 0;
	i = 0;
	while (game->file_content[i] != NULL)
	{
		process_line(game, game->file_content[i], &map_started, &map_ended);
		i++;
	}
}

int	parse_file(t_game *game, char *filename)
{
	game->file_content = read_file(game, filename);
	if (!game->file_content)
		return (0);
	parse_lines(game);
	if (game->map_data.height == 0 || !game->map_data.map)
		error_exit("Map is empty", game);
	normalize_map(&game->map_data);
	validate_map(game);
	set_player_start(game);
	if (game->floor_color == -1 || game->ceiling_color == -1)
		error_exit("Floor or ceiling color not set", game);
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
