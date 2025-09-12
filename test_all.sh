#!/bin/bash

# cub3D 実行ファイル
CUB3D_EXEC="./cub3D"

# マップファイルが入っているディレクトリ
MAP_DIR="./maps_cp/bad"

# ログディレクトリ
LOG_DIR="./logs"
mkdir -p "$LOG_DIR"

# 並列実行数 (CPUコア数に合わせて調整)
PARALLEL=4

# 色定義
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# テスト用関数
test_map() {
    local file="$1"
    local log_file="$LOG_DIR/$(basename "$file").log"

    # valgrind で実行（サマリだけ出す）
    valgrind --leak-check=full --errors-for-leak-kinds=all \
             --show-leak-kinds=all --quiet \
             --log-file="$log_file" \
             "$CUB3D_EXEC" "$file"

    # エラー判定
    if grep -q -E "Error|Map is not enclosed" "$log_file"; then
        echo -e "$(basename "$file") | ${RED}Failed${NC}"
    elif grep -q "definitely lost: 0 bytes in 0 blocks" "$log_file"; then
        echo -e "$(basename "$file") | ${GREEN}Passed (No leaks)${NC}"
    else
        echo -e "$(basename "$file") | ${YELLOW}Passed (Leaks detected)${NC}"
    fi
}

export -f test_map
export CUB3D_EXEC
export LOG_DIR
export RED GREEN YELLOW NC

echo "=== Start cub3D Batch Test (Parallel: $PARALLEL, with Valgrind) ==="
printf "%-30s | %s\n" "Map File" "Result"
echo "-------------------------------------------"

# 並列実行
find "$MAP_DIR" -name "*.cub" | xargs -n 1 -P "$PARALLEL" -I {} bash -c 'test_map "$@"' _ {}

echo "=== Batch Test Completed ==="
