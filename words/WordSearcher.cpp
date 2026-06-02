#include "WordSearcher.h"

// DFS
bool WordSearcher::dfs(const GameBoard& board, const std::vector<std::string>& target_letters, size_t index,
                       int r, int c, std::vector<std::vector<bool>>& visited,
                       int target_r, int target_c, bool& used_new_cell) {
    
    // Если успешно дошли до конца вектора букв слова возвращаем использования новой клетки
    if (index == target_letters.size()) {
        return used_new_cell;
    }

    //  выход за границы поля, посещенная клетка, или буква на поле не совпадает с  буквой слова
    if (r < 0 || r >= 5 || c < 0 || c >= 5 || visited[r][c] || board.getLetter(r, c) != target_letters[index]) {
        return false;
    }
    visited[r][c] = true;
    
    bool backup_new_cell = used_new_cell;
    if (r == target_r && c == target_c) {
        used_new_cell = true;
    }

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    // Пробуем пойти во всех 4 направлениях
    for (int i = 0; i < 4; ++i) {
        if (dfs(board, target_letters, index + 1, r + dr[i], c + dc[i], visited, target_r, target_c, used_new_cell)) {
            return true;
        }
    }

    visited[r][c] = false;
    used_new_cell = backup_new_cell;
    return false;
}

bool WordSearcher::canFormWord(const GameBoard& board, const std::string& word, int target_r, int target_c) {
    std::vector<std::string> target_letters;
    // Безопасное разбиение UTF-8 строки посимвольно
    for (size_t i = 0; i < word.length(); ) {
        unsigned char c = word[i];
        if (c >= 0x80) {
            target_letters.push_back(word.substr(i, 2)); // Забираем 2 байта кириллицы
            i += 2;
        } else {
            target_letters.push_back(word.substr(i, 1)); // Забираем 1 байт
            i += 1;
        }
    }

    // Пытаемся запустить поиск слова, начиная абсолютно с каждой ячейки поля
    for (int r = 0; r < 5; ++r) {
        for (int c = 0; c < 5; ++c) {
            std::vector<std::vector<bool>> visited(5, std::vector<bool>(5, false));
            bool used_new_cell = false;
            if (dfs(board, target_letters, 0, r, c, visited, target_r, target_c, used_new_cell)) {
                return true;
            }
        }
    }
    return false; 
}
