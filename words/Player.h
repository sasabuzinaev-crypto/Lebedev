#ifndef PLAYER_H
#define PLAYER_H 
#include <string> 
class Player {
private:
    std::string name; // хранит имя игрока 
    int score;        // хранит текущие очки игрока

public:
    // создает игрока с заданным именем
    Player(const std::string& player_name);

    // Метод получения имени игрока
    std::string getName() const;

    // Метод  получения текущих очков игрока
    int getScore() const;

    // Метод для добавления очков к текущему счету игрока
    void addPoints(int points);
};

#endif