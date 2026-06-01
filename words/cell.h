#ifndef CELL_H
#define CELL_H

struct Cell {
    int r, c;
    Cell(int row = 0, int col = 0) : r(row), c(col) {}
    bool operator==(const Cell& other) const { return r == other.r && c == other.c; }
};

#endif
