/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:02:17 by kotasakatsu       #+#    #+#             */
/*   Updated: 2025/08/22 19:44:23 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cub.h"
#include <stdio.h>

int	is_map_line(char *line)
{
	int	i;

	if (!line || line[0] == '\0')
		return (0);
	i = 0;
	while (line[i] != '\0')
	{
		if (!(line[i] == '1' || line[i] == '0' || line[i] == 'N'
				|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W'
				|| line[i] == ' '))
			return (0);
		i++;
	}
	return (1);
}

// int	parse_file(t_game *game, char *filename)
// {
// }

#include <stdio.h>

int	is_map_line(char *line); // ここに作った関数の宣言

int	main(void)
{
	size_t	i;

	char *tests[] = {
		"1111",
		"1001",
		"1N01",
		"1 0 1",
		"1234", // NG
		"abc",  // NG
		"",     // NG
		NULL    // NG
	};
	for (i = 0; i < sizeof(tests) / sizeof(tests[0]); i++)
	{
		printf("Test %zu: \"%s\" -> %d\n", i, tests[i] ? tests[i] : "NULL",
			is_map_line(tests[i]));
	}
	return (0);
}
