#include "Player.h"

Player::Player(const std::string& player_name) : name(player_name), score(0) {}

std::string Player::getName() const {
    return name;
}

int Player::getScore() const {
    return score;
}

void Player::addPoints(int points) {
    score += points;
}
