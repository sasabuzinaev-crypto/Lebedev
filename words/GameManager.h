#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "board.h"
#include "GameDictionary.h"
#include "WordSearcher.h"
#include <vector>
#include <string>

class Player {
private:
    std::string name; // Имя игрока
    int score;        // Количество набранных игроком очков

public:
    // инициализирует имя переданным значением, а начальный счет ставит в 0
    Player(std::string n) : name(n), score(0) {}

    std::string getName() const { return name; }

    int getScore() const { return score; }

    void addPoints(int p) { score += p; }
};

// Главный управляющий класс игры
class GameManager {
private:
    GameBoard board;                 // Игровое поле
    GameDictionary dictionary;       // Словарь игры
    WordSearcher searcher;           // Поисковик слов "змейкой"
    std::vector<Player> players;     // Список всех участвующих игроков
    int current_player_index;        // Индекс игрока, который совершает ход прямо сейчас

public:
    // настраивает игроков, словарь и выставляет стартовое слово на поле
    GameManager(int players_count, const std::string& start_word, const std::string& dict_filename);

    // обрабатывает ходы, ввод данных, проверки и начисление очков
    void start();
};

#endif
