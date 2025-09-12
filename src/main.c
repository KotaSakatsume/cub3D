/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:03:06 by kotasakatsu       #+#    #+#             */
/*   Updated: 2025/09/12 18:09:26 by kosakats         ###   ########.fr       */
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

void	error_exit(char *message, t_game *game)
{
	write(2, "Error\n", 6);
	if (message)
	{
		write(2, message, strlen(message));
		write(2, "\n", 1);
	}
	if (game)
	{
		free_file_content(game->file_content);
		free_map(&game->map_data);
		free_textures(game);
		free(game);
	}
	exit(1);
}

// int	check_extension(const char *filename, const char *extension)
// {
// 	size_t	len;

// 	if (!filename)
// 		return (0);
// 	len = strlen(filename);
// 	if (len < 4 || strncmp(filename + len - 4, extension, 5))
// 		return (0);
// 	return (1);
// }

int	main(int argc, char **argv)
{
	t_game	*game;

	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return (write(2, "Error\nMemory allocation failed\n", 31));
	if (argc != 2)
		return (free(game), write(2, "Error\nUsage: ./cub3d <map.cub>\n", 31),
			1);
	if (!check_extension(argv[1], ".cub"))
		return (free(game), write(2, "Error\nFile must have .cub extension\n",
				36));
	init_game(game);
	if (!parse_file(game, argv[1]))
		return (1);
	if (set_texture(game) == 1)
	{
		free_game(game);
		return (1);
	}
	set_mlx_hook(game);
	mlx_loop(game->mlx);
	return (0);
}
