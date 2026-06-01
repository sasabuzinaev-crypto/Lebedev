#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <string>
#include <vector>

class GameBoard {
private:
    char board[5][5]; // Сетка 5х5 из обычных букв char

public:
    GameBoard();

    // Заполняет центральную (вторую) строку стартовым словом
    void initCentralWord(const std::string& word);

    // Рисует поле в консоли
    void display() const;

    // Ставит букву в указанные координаты
    void setLetter(int row, int col, char letter);

    // Возвращает букву из указанной ячейки
    char getLetter(int row, int col) const;

    // Проверяет, пуста ли клетка
    bool isEmpty(int row, int col) const;

    // Проверяет, имеет ли клетка хоть одного соседа (чтобы не ставить букву в воздухе)
    bool hasNeighbors(int row, int col) const;
};

#endif
