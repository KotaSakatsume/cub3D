/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:07:57 by kotasakatsu       #+#    #+#             */
/*   Updated: 2025/09/08 18:56:29 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	process_node(t_game *game, int **visited, t_queue *node,
		t_queue **queue)
{
	int		x;
	int		y;
	char	c;

	x = node->x;
	y = node->y;
	free(node);
	if (x < 0 || y < 0 || x >= game->map_data.width
		|| y >= game->map_data.height)
		error_exit("Map has a hole (out of bounds)", game);
	if (visited[y][x])
		return ;
	c = game->map_data.map[y][x];
	if (!is_valid_char(c))
		error_exit("Invalid character in map", game);
	visited[y][x] = 1;
	if (c == '0' || is_player(c) || c == ' ')
	{
		enqueue(queue, x + 1, y);
		enqueue(queue, x - 1, y);
		enqueue(queue, x, y + 1);
		enqueue(queue, x, y - 1);
	}
}

static t_queue	*dequeue(t_queue **head)
{
	t_queue	*node;

	if (!*head)
		return (NULL);
	node = *head;
	*head = (*head)->next;
	return (node);
}

void	bfs_validate(t_game *game, int **visited, t_queue *queue)
{
	t_queue	*node;

	node = dequeue(&queue);
	while (node != NULL)
	{
		process_node(game, visited, node, &queue);
		node = dequeue(&queue);
	}
}
