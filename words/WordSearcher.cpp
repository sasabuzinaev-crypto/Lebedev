#include "WordSearcher.h"

//  функция поиска пути 
bool WordSearcher::dfs(const GameBoard& board, const std::string& word, int index, 
                       int r, int c, std::vector<std::vector<bool>>& visited, 
                       int target_r, int target_c, bool& used_new_cell) {
    
    if (index == word.length()) {
        return used_new_cell; // Возвращаем true только если змейка наступила на новую букву хода
    }

    // Проверяем выход за границы, повторное посещение ячейки 
    // или несовпадение буквы на поле с текущей буквой искомого слова
    if (r < 0 || r >= 5 || c < 0 || c >= 5 || visited[r][c] || board.getLetter(r, c) != word[index]) {
        return false; 
    }

    // Отмечаем текущую ячейку как посещенную в этой ветке поиска
    visited[r][c] = true;
    
    bool backup_new_cell = used_new_cell;
    // Если наши текущие координаты совпали с координатами новой буквы игрока 
    if (r == target_r && c == target_c) {
        used_new_cell = true;
    }

    // Направления шагов вверх, вниз, влево, вправо
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; ++i) {
        if (dfs(board, word, index + 1, r + dr[i], c + dc[i], visited, target_r, target_c, used_new_cell)) {
            return true; // Если змейка успешно достроилась в этой стороне, передаем true наверх
        }
    }

    //  Если ни одна сторона не подошла снимаем отметку посещения с ячейки
    visited[r][c] = false;
    used_new_cell = backup_new_cell;
    return false; 
}

// Главная функция запуска поиска слова на доске
bool WordSearcher::canFormWord(const GameBoard& board, const std::string& word, int target_r, int target_c) {
    // Сканируем циклом всё поле 5x5 
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (board.getLetter(i, j) == word[0]) {
                std::vector<std::vector<bool>> visited(5, std::vector<bool>(5, false));
                bool used_new_cell = false; // Стартовый флаг использования новой ячейки
                
                // Запускаем рекурсивный поиск DFS 
                if (dfs(board, word, 0, i, j, visited, target_r, target_c, used_new_cell)) {
                    return true; 
                }
            }
        }
    }
    return false; 
}
