/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:24:41 by kosakats          #+#    #+#             */
/*   Updated: 2025/01/30 13:59:55 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		c;
	t_string	ret;

	ret.str = NULL;
	ret.len = 0;
	ret.capa = 0;
	while (1)
	{
		c = ft_getc(fd);
		if (c == EOF)
			break ;
		ft_putc(&ret, c);
		if (c == '\n')
			break ;
	}
	if (ret.len > 0)
		ft_putc(&ret, '\0');
	if (ret.str == NULL || ret.len == 0)
	{
		free(ret.str);
		return (NULL);
	}
	return (ret.str);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	printf("BUFFER_SIZE;%d\n", BUFFER_SIZE);
// 	fd = open("text.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Failed to open file");
// 		return (1);
// 	}
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }

// int	main(void)
// {
// 	int	fd;
// 	int	c;

// 	fd = open("text.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	while (1)
// 	{
// 		c = ft_getc(fd);
// 		if (c == EOF)
// 			break ;
// 		printf("%c", c);
// 	}
// 	close(fd);
// 	return (0);
// }

// #include "get_next_line.h"
// #include <fcntl.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>

// char	*get_next_line(int fd)
// {
// 	static int	n = 0;
// 	static int	start = 0;
// 	char		*line;
// 	int			end;
// 	static char	buf[BUFFER_SIZE];

// 	if (n == 0)
// 	{
// 		n = read(fd, buf, BUFFER_SIZE);
// 		if (n <= 0)
// 			return (NULL);
// 		start = 0;
// 	}
// 	end = start;
// 	while (end < n && buf[end] != '\n')
// 		end++;
// 	line = malloc(end - start + 2);
// 	if (!line)
// 		return (NULL);
// 	memcpy(line, buf + start, end - start);
// 	line[end - start] = '\0';
// 	if (end < n && buf[end] == '\n')
// 	{
// 		line[end - start] = '\n';
// 		line[end - start + 1] = '\0';
// 		start = end + 1;
// 	}
// 	else
// 	{
// 		n = 0;
// 	}
// 	return (line);
// }

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("text.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
