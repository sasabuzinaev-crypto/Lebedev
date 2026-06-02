#include "board.h"
#include <iostream>

// обходит всю матрицу 5x5 и заполняет каждую ячейку строкой со знаком пробела
GameBoard::GameBoard() {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            board[i][j] = " ";
        }
    }
}

void GameBoard::initCentralWord(const std::string& word) {
    for (int j = 0; j < 5; ++j) {
        if (j * 2 < word.length()) {
            board[2][j] = word.substr(j * 2, 2);
        } else {
            board[2][j] = " ";
        }
    }
}
void GameBoard::display() const {
    std::cout << "    0   1   2   3   4 \n";
    std::cout << "  +---+---+---+---+---\n";
    for (int i = 0; i < 5; ++i) {
        std::cout << i << " | ";
        for (int j = 0; j < 5; ++j) {
            std::cout << board[i][j] << " | ";
        }
        std::cout << "\n  +---+---+---+---+---\n";
    }
}

void GameBoard::setLetter(int row, int col, const std::string& letter) {
    board[row][col] = letter;
}

std::string GameBoard::getLetter(int row, int col) const {
    return board[row][col];
}

bool GameBoard::isEmpty(int row, int col) const {
    return board[row][col] == " ";
}

// Проверяет 4 соседние клетки
bool GameBoard::hasNeighbors(int row, int col) const {
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; ++i) {
        int nr = row + dr[i];
        int nc = col + dc[i];
        if (nr >= 0 && nr < 5 && nc >= 0 && nc < 5) {
            if (!isEmpty(nr, nc)) {
                return true;
            }
        }
    }
    return false;
}
