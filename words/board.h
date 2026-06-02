#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <string>
#include <vector>

// Класс игрового поля 5x5
class GameBoard {
private:
    std::string board[5][5];

public:
    GameBoard();

    // Заполняет центральную строку стартовым словом из 5 букв
    void initCentralWord(const std::string& word);

    // Отрисовывает сетку поля в консоли
    void display() const;

    // Устанавливает букву в указанные координаты поля
    void setLetter(int row, int col, const std::string& letter);

    // Возвращает букву из указанной ячейки поля
    std::string getLetter(int row, int col) const;

    // Проверяет пуста ли указанная клетка
    bool isEmpty(int row, int col) const;

    // Проверяет граничит ли клетка хотя бы с одной уже заполненной буквой ячейкой
    bool hasNeighbors(int row, int col) const;
};

#endif
