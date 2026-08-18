#pragma once
#include <vector>
#include <string>
#include <raylib.h>
#include "Globals.h"
#include "Ship.h"

class Board {
private:
    CellState grid[10][10];
    std::vector<Ship> ships;

public:
    static const int CELL_SIZE = 40;

    Board();
    bool placeShip(Ship newShip, int row, int col, Orientation dir);
    bool receiveAttack(int row, int col);
    bool allShipsSunk();

    CellState getCellState(int row, int col) {
        return grid[row][col];
    }

    void markCell(int row, int col, const std::string& status);
    bool isAlreadyGuessed(int row, int col);
    void draw(int offsetX, int offsetY, bool hideShips = false);
};