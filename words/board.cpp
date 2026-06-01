#include "board.h"
#include <iostream>
GameBoard::GameBoard() {
    // Вложенными циклами заполняем все 25 ячеек пробелами чтобы поле изначально было пустым
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            board[i][j] = ' '; 
        }
    }
}

// Запись стартового слова на поле
void GameBoard::initCentralWord(const std::string& word) {
    for (int j = 0; j < 5; ++j) {
        board[2][j] = word[j]; 
    }
}

// Отрисовка игрового поля 
void GameBoard::display() const {
    std::cout << "    0   1   2   3   4 \n"; 
    std::cout << "  +---+---+---+---+---+\n"; 
    for (int i = 0; i < 5; ++i) {
        std::cout << i << " | "; 
        for (int j = 0; j < 5; ++j) {
            std::cout << board[i][j] << " | "; // Печатаем букву внутри ячейки и разделитель
        }
        std::cout << "\n  +---+---+---+---+---+\n"; 
    }
}

// Устанавливает символ в массив по заданным координатам
void GameBoard::setLetter(int row, int col, char letter) {
    board[row][col] = letter;
}

// Возвращает символ буквы из массива по заданным координатам
char GameBoard::getLetter(int row, int col) const {
    return board[row][col];
}

// Если в ячейке находится пробел значит она пуста — возвращаем true
bool GameBoard::isEmpty(int row, int col) const {
    return board[row][col] == ' ';
}

// Проверка наличия соседних букв 
bool GameBoard::hasNeighbors(int row, int col) const {
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    
    // Проверяем все 4 стороны вокруг клетки
    for (int i = 0; i < 4; ++i) {
        int nr = row + dr[i]; 
        int nc = col + dc[i]; 
        
        // Проверяем, не вышли ли соседние координаты за границы 
        if (nr >= 0 && nr < 5 && nc >= 0 && nc < 5) {
            if (board[nr][nc] != ' ') return true;
        }
    }
    return false; 
}