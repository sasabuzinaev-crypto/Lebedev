#ifndef BOARD_H
#define BOARD_H 

#include <string>
#include <vector>

class GameBoard {
private:
    char board[5][5]; //  5x5, хранящий одиночные символы букв

public:
    //  создает и очищает игровое поле
    GameBoard();

    // Метод для записи начального слова в центральную строку поля
    void initCentralWord(const std::string& word);
    void display() const;
    void setLetter(int row, int col, char letter);

    // Метод, возвращающий букву, которая сейчас стоит в указанных координатах
    char getLetter(int row, int col) const;

    // Проверка: пуста ли клетка 
    bool isEmpty(int row, int col) const;

    // Проверка: касается ли ячейка хотя бы одной уже занятой клетки по соседству
    bool hasNeighbors(int row, int col) const;
};

#endif