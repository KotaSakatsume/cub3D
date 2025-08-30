/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 21:49:17 by kosakats          #+#    #+#             */
/*   Updated: 2025/01/30 13:59:57 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	ft_getc(int fd)
{
	static char	buf[BUFFER_SIZE];
	static char	*bufp;
	static int	n = 0;

	if (n == 0)
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n <= 0)
			return (EOF);
		bufp = buf;
	}
	if (n > 0)
	{
		n--;
		return ((unsigned char)*bufp++);
	}
	return (EOF);
}

int	extend_capacity(t_string *str)
{
	size_t	new_capa;
	char	*new_str;
	size_t	i;

	if (str->capa == 0)
		new_capa = 16;
	else
		new_capa = str->capa * 2;
	new_str = malloc(new_capa);
	if (!new_str)
	{
		free(str->str);
		return (-1);
	}
	i = 0;
	while (i < str->len)
	{
		new_str[i] = str->str[i];
		i++;
	}
	free(str->str);
	str->str = new_str;
	str->capa = new_capa;
	return (0);
}

int	ft_putc(t_string *str, char c)
{
	if (str->len + 1 >= str->capa)
	{
		if (extend_capacity(str) == -1)
			return (-1);
	}
	str->str[str->len] = c;
	str->len++;
	return (0);
}
