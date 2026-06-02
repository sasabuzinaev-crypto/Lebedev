#ifndef WORDSEARCHER_H
#define WORDSEARCHER_H

#include "board.h"
#include <string>
#include <vector>

// для проверки возможности составления слова змейкой на поле
class WordSearcher {
private:
    // DFS
    bool dfs(const GameBoard& board, const std::vector<std::string>& target_letters, size_t index,
             int r, int c, std::vector<std::vector<bool>>& visited,
             int target_r, int target_c, bool& used_new_cell);

public:
    // можно ли обойти поле и собрать слово обязательно задействовав новую клетку
    bool canFormWord(const GameBoard& board, const std::string& word, int target_r, int target_c);
};

#endif
