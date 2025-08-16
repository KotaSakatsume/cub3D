/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kotasakatsume <kotasakatsume@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 13:03:06 by kotasakatsu       #+#    #+#             */
/*   Updated: 2025/08/16 14:55:08 by kotasakatsu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void error_exit(char *message)
{
    write(2, "Error\n", 6);
    if (message)
        write(2, message, strlen(message));
    exit(1);
}

int main(int argc, char **argv)
{
    t_game  game;

    // 1. 引数のチェック
    if (argc != 2)
        return (error_exit("Usage: ./cub3d <map.cub>"), 1);
    if (!check_extension(argv[1], ".cub"))
        return (error_exit("File must have .cub extension"), 1);

    // 2. パース処理の開始
    if (!parse_file(&game, argv[1]))
        return (1); // parse_file内でエラーメッセージは出力済み

    // 3. ゲームの初期化と実行
    init_game(&game);
    run_game(&game);
    
    return (0);
}
