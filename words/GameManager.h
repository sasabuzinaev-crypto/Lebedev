#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H 

#include "board.h"
#include "Player.h"
#include "GameDictionary.h"
#include "WordSearcher.h"
#include <vector>
#include <string>

class GameManager {
private:
    GameBoard board;                 // Объект игрового поля 5x5
    GameDictionary dictionary;       // Объект судьи-словаря
    WordSearcher searcher;           // Объект поисковика геометрических змеек
    std::vector<Player> players;     // Список  всех участвующих игроков
    int current_player_index;        // Номер игрока, который должен ходить прямо сейчас

public:
   
    GameManager(int players_count, const std::string& start_word, const std::string& dict_filename);
    
    void start();
};

#endif