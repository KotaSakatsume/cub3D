/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkuida <reprise39@yahoo.co.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 10:32:38 by mkuida            #+#    #+#             */
/*   Updated: 2025/08/28 16:52:47 by mkuida           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0)
		return ;
	if (x >= WINDOW_WIDTH || y >= WINDOW_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	my_mlx_pixel_get(t_img *data, int x, int y)
{
	char	*dst;

	x = max(x, 0);
	x = min(x, (data->width) - 1);
	y = max(y, 0);
	y = min(y, (data->height) - 1);
	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	return (*(unsigned int *)dst);
}
