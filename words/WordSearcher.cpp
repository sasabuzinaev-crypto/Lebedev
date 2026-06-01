#include "WordSearcher.h"

bool WordSearcher::dfs(const GameBoard& board, const std::string& word, int index,
                       int r, int c, std::vector<std::vector<bool>>& visited,
                       int target_r, int target_c, bool& used_new_cell) {
    
    // Если нашли все буквы слова
    if (index == word.length()) {
        return used_new_cell; // Возвращаем true, только если наступили на новую клетку
    }

    // Проверка границ поля и совпадения буквы
    if (r < 0 || r >= 5 || c < 0 || c >= 5 || visited[r][c] || board.getLetter(r, c) != word[index]) {
        return false;
    }

    // Отмечаем клетку как посещенную
    visited[r][c] = true;
    
    // Флаг: наступили ли мы в процессе на ту самую новую букву игрока
    bool backup_new_cell = used_new_cell;
    if (r == target_r && c == target_c) {
        used_new_cell = true;
    }

    // Направления движения: вверх, вниз, влево, вправо
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; ++i) {
        if (dfs(board, word, index + 1, r + dr[i], c + dc[i], visited, target_r, target_c, used_new_cell)) {
            return true;
        }
    }

    // Откат (бэкпэкинг): убираем отметку, если этот путь привел в тупик
    visited[r][c] = false;
    used_new_cell = backup_new_cell;
    return false;
}

bool WordSearcher::canFormWord(const GameBoard& board, const std::string& word, int target_r, int target_c) {
    // Пробуем запустить поиск слова с каждой клетки поля
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (board.getLetter(i, j) == word[0]) {
                std::vector<std::vector<bool>> visited(5, std::vector<bool>(5, false));
                bool used_new_cell = false;
                if (dfs(board, word, 0, i, j, visited, target_r, target_c, used_new_cell)) {
                    return true;
                }
            }
        }
    }
    return false;
}
