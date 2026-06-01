#ifndef WORDSEARCHER_H
#define WORDSEARCHER_H

#include "GameBoard.h"
#include <string>
#include <vector>

class WordSearcher {
private:
    bool dfs(const GameBoard& board, const std::string& word, int index,
             int r, int c, std::vector<std::vector<bool>>& visited,
             int target_r, int target_c, bool& used_new_cell);

public:
    // Проверяет, можно ли составить слово змейкой на поле
    // target_r и target_c — это координаты буквы, которую ввёл игрок на этом ходу
    bool canFormWord(const GameBoard& board, const std::string& word, int target_r, int target_c);
};

#endif
