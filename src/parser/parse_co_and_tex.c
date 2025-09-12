/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_co_and_tex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:07:57 by kotasakatsu       #+#    #+#             */
/*   Updated: 2025/09/12 11:02:30 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

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
	*texture_path = ft_strdup(path);
	if (!*texture_path)
		error_exit("Malloc failed for texture path", game);
}

static void	validate_and_assign_color(t_game *game, char **rgb, int *color)
{
	int	r;
	int	g;
	int	b;

	if (!rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		free_split(rgb);
		error_exit("Invalid color format", game);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		free_split(rgb);
		error_exit("Color values out of range", game);
	}
	*color = (r << 16) | (g << 8) | b;
}

void	parse_color(t_game *game, const char *color_str, int *color)
{
	char	**rgb;

	if (*color != -1)
		error_exit("Duplicate color definition", game);
	rgb = ft_split(color_str, ',');
	if (!rgb)
		error_exit("Failed to allocate memory for color", game);
	validate_and_assign_color(game, rgb, color);
	free_split(rgb);
}
