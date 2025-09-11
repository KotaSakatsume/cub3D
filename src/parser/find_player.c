/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:07:57 by kotasakatsu       #+#    #+#             */
/*   Updated: 2025/09/09 16:56:46 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	enqueue(t_queue **head, int x, int y)
{
	t_queue	*node;
	t_queue	*tmp;

	node = malloc(sizeof(t_queue));
	if (!node)
		return ;
	node->x = x;
	node->y = y;
	node->next = NULL;
	if (!*head)
		*head = node;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

void	set_player_queue(t_queue **queue, int x, int y, int *found)
{
	if (!*found)
	{
		enqueue(queue, x, y);
		*found = 1;
	}
}

void	find_player(t_game *game, t_queue **queue)
{
	find_player_loop(game, queue);
}
