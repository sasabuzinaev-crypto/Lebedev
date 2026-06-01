#ifndef WORDSEARCHER_H
#define WORDSEARCHER_H 

#include "board.h"
#include <string>
#include <vector>

class WordSearcher {
private:
    //  метод алгоритма DFS 
    bool dfs(const GameBoard& board, const std::string& word, int index, 
             int r, int c, std::vector<std::vector<bool>>& visited, 
             int target_r, int target_c, bool& used_new_cell);

public:
    //  можно ли составить слово змейкой на текущем поле
    bool canFormWord(const GameBoard& board, const std::string& word, int target_r, int target_c);
};

#endif