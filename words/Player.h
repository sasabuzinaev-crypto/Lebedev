#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
private:
    std::string name;
    int score;

public:
    Player(const std::string& player_name);

    std::string getName() const;
    int getScore() const;
    void addPoints(int points);
};

#endif
