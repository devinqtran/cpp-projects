#pragma once
#include <vector>
#include "Globals.h"
#include "Ship.h"

class Board {
private:
    CellState grid[10][10];
    std::vector<Ship> fleet;

public:
    Board();
    bool placeShip(Ship newShip, int row, int col, Orientation dir);
    bool receiveAttack(int row, int col);

    CellState getCellState(int row, int col) {
        return grid[row][col];
    }
};