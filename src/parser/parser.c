/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosakats <kosakats@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:02:17 by kotasakatsu       #+#    #+#             */
/*   Updated: 2025/08/30 16:54:44 by kosakats         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
static char	*process_line(char *line)
{
	size_t	len;

	len = strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

// 行追加用関数（動的に拡張）+ NULL終端対応
char	**add_line(char **file_content, int *count, int *capacity, char *line)
{
	int		new_capacity;
	char	**new_content;

	// NULLなら終端追加
	if (line == NULL)
	{
		file_content[*count] = NULL;
		return (file_content);
	}
	// 容量不足なら拡張
	if (*count >= *capacity)
	{
		new_capacity = (*capacity == 0) ? 10 : (*capacity * 2);
		new_content = malloc(sizeof(char *) * new_capacity);
		if (!new_content)
			return (NULL);
		for (int i = 0; i < *count; i++)
			new_content[i] = file_content[i];
		free(file_content);
		file_content = new_content;
		*capacity = new_capacity;
	}
	file_content[*count] = strdup(line);
	if (!file_content[*count])
		return (NULL);
	(*count)++;
	return (file_content);
}

char	**read_file(t_game *game, char *filename)
{
	char	**file_content;
	int		count;
	int		capacity;
	int		fd;
	char	*line;

	file_content = NULL;
	count = 0;
	capacity = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open file\n", game);
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
	// NULL終端を追加
	file_content = add_line(file_content, &count, &capacity, NULL);
	if (!file_content)
		error_exit("Malloc failed\n", game);
	close(fd);
	return (file_content);
}

int	parse_file(t_game *game, char *filename)
{
	char	**file_content;
	int		i;

	// 1. ファイルを読み込み、内容を文字列の配列として取得
	file_content = read_file(game, filename); // read_fileはchar**を返すように修正
	if (!file_content)
		return (0);
	i = 0;
	while (file_content[i] != NULL)
	{
		printf("%s\n", file_content[i]);
		i++;
	}
	// 2. シーン要素とマップデータをパース
	// if (!parse_content(game, file_content))
	// {
	// 	// parse_content内でエラー処理が行われている
	// 	// メモリを解放してから終了
	// 	free_file_content(file_content);
	// 	return (0);
	// }
	// // 3. パース後の検証
	// if (!validate_map(game))
	// {
	// 	// validate_map内でエラー処理が行われている
	// 	// メモリを解放してから終了
	// 	free_file_content(file_content);
	// 	return (0);
	// }
	// // 全て成功したらメモリを解放して1を返す
	// free_file_content(file_content);
	return (1);
}

// int	is_map_line(char *line); // ここに作った関数の宣言

// int	main(void)
// {
// 	size_t	i;

// 	char *tests[] = {
// 		"1111",
// 		"1001",
// 		"1N01",
// 		"1 0 1",
// 		"1234", // NG
// 		"abc",  // NG
// 		"",     // NG
// 		NULL    // NG
// 	};
// 	for (i = 0; i < sizeof(tests) / sizeof(tests[0]); i++)
// 	{
// 		printf("Test %zu: \"%s\" -> %d\n", i, tests[i] ? tests[i] : "NULL",
// 			is_map_line(tests[i]));
// 	}
// 	return (0);
// }
