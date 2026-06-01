#include "board.h"
#include <iostream>

GameBoard::GameBoard() {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            board[i][j] = ' '; // Заполняем поле пробелами
        }
    }
}

void GameBoard::initCentralWord(const std::string& word) {
    for (int j = 0; j < 5; ++j) {
        board[2][j] = word[j]; // Записываем в 2-ю строку
    }
}

void GameBoard::display() const {
    std::cout << "    0   1   2   3   4 \n";
    std::cout << "  +---+---+---+---+---+\n";
    for (int i = 0; i < 5; ++i) {
        std::cout << i << " | ";
        for (int j = 0; j < 5; ++j) {
            std::cout << board[i][j] << " | ";
        }
        std::cout << "\n  +---+---+---+---+---+\n";
    }
}

void GameBoard::setLetter(int row, int col, char letter) {
    board[row][col] = letter;
}

char GameBoard::getLetter(int row, int col) const {
    return board[row][col];
}

bool GameBoard::isEmpty(int row, int col) const {
    return board[row][col] == ' ';
}

bool GameBoard::hasNeighbors(int row, int col) const {
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    for (int i = 0; i < 4; ++i) {
        int nr = row + dr[i];
        int nc = col + dc[i];
        if (nr >= 0 && nr < 5 && nc >= 0 && nc < 5) {
            if (board[nr][nc] != ' ') return true;
        }
    }
    return false;
}
