#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "GameBoard.h"
#include "Player.h"
#include "GameDictionary.h"
#include "WordSearcher.h"
#include <vector>
#include <string>

class GameManager {
private:
    GameBoard board;
    GameDictionary dictionary;
    WordSearcher searcher;
    std::vector<Player> players;
    int current_player_index;

public:
    GameManager(int players_count, const std::string& start_word, const std::string& dict_filename);
    void start();
};

#endif
