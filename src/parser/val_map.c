/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:07:57 by kotasakatsu       #+#    #+#             */
/*   Updated: 2025/09/09 12:14:54 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	**init_visited(int width, int height)
{
	int	**visited;
	int	y;

	visited = malloc(sizeof(int *) * height);
	y = 0;
	while (y < height)
	{
		visited[y] = calloc(width, sizeof(int));
		y++;
	}
	return (visited);
}

void	find_player_loop(t_game *game, t_queue **queue)
{
	char	**map;
	int		width;
	int		height;
	int		y;
	int		x_found[2];

	map = game->map_data.map;
	width = game->map_data.width;
	height = game->map_data.height;
	y = 0;
	x_found[1] = 0;
	while (y < height && !x_found[1])
	{
		x_found[0] = 0;
		while (x_found[0] < width)
		{
			if (is_player(map[y][x_found[0]]))
				set_player_queue(queue, x_found[0], y, &x_found[1]);
			x_found[0]++;
		}
		y++;
	}
	if (!x_found[1])
		error_exit("No player on map", game);
}

void	validate_map(t_game *game)
{
	int		**visited;
	t_queue	*queue;

	visited = init_visited(game->map_data.width, game->map_data.height);
	queue = NULL;
	find_player(game, &queue);
	bfs_validate(game, visited, queue);
	free_visited(visited, game->map_data.height);
}
