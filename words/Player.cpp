#include "Player.h" 
//  инициализирует имя переданным значением а начальный счет ставит в 0
Player::Player(const std::string& player_name) : name(player_name), score(0) {}

// возвращает текстовое имя игрока наружу
std::string Player::getName() const {
    return name;
}

//  возвращает число набранных очков игрока наружу
int Player::getScore() const {
    return score;
}

//  увеличивает счет игрока на переданное число очков
void Player::addPoints(int points) {
    score += points; 
}