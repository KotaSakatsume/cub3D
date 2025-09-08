/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:07:57 by kotasakatsu       #+#    #+#             */
/*   Updated: 2025/09/08 18:32:27 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// 配列を拡張する
static char	**resize_content(char **file_content, int *capacity, int count)
{
	char	**new_content;
	int		new_capacity;
	int		i;

	if (*capacity == 0)
		new_capacity = 10;
	else
		new_capacity = *capacity * 2;
	new_content = malloc(sizeof(char *) * new_capacity);
	if (!new_content)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_content[i] = file_content[i];
		i++;
	}
	free(file_content);
	*capacity = new_capacity;
	return (new_content);
}

// 行を追加する
char	**add_line(char **file_content, int *count, int *capacity, char *line)
{
	if (line == NULL)
	{
		file_content[*count] = NULL;
		return (file_content);
	}
	if (*count >= *capacity)
	{
		file_content = resize_content(file_content, capacity, *count);
		if (!file_content)
			return (NULL);
	}
	file_content[*count] = strdup(line);
	if (!file_content[*count])
		return (NULL);
	(*count)++;
	return (file_content);
}

static char	*process_line(char *line)
{
	size_t	len;

	len = strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

static int	open_file(t_game *game, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open file\n", game);
	return (fd);
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
	fd = open_file(game, filename);
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
