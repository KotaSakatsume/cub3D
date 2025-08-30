/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:58:02 by kosakats          #+#    #+#             */
/*   Updated: 2025/01/30 13:59:53 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000000
# endif

typedef struct s_string
{
	char	*str;
	size_t	len;
	size_t	capa;
}			t_string;

char		*get_next_line(int fd);
int			ft_putc(t_string *str, char c);
char		ft_getc(int fd);
int			extend_capacity(t_string *str);

#endif
