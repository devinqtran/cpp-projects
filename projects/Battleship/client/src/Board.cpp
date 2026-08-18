#include "Board.h"
#include <vector>
#include <iostream>
#include "raylib.h"
#include "Globals.h"

// Constructor - creates empty 10x10 grid
Board::Board()
{
    for (int row = 0; row < 10; row++)
    {
        for (int col = 0; col < 10; col++)
        {
            grid[row][col] = EMPTY;
        }
    }
}

bool Board::placeShip(Ship newShip, int row, int col, Orientation dir)
{
    // 1. BOUNDS CHECK: Make sure the ship doesn't go off the edge of the board
    if (dir == HORIZONTAL)
    {
        if (col + newShip.size > 10)
            return false;
    }
    else
    { // VERTICAL
        if (row + newShip.size > 10)
            return false;
    }

    // 2. OVERLAP CHECK: Make sure there aren't any ships already in these spaces
    for (int i = 0; i < newShip.size; i++)
    {
        if (dir == HORIZONTAL)
        {
            if (grid[row][col + i] != EMPTY)
                return false;
        }
        else
        { // VERTICAL
            if (grid[row + i][col] != EMPTY)
                return false;
        }
    }

    // 3. PLACE SHIP: If bounds and overlaps are clear, physically place it on the grid
    for (int i = 0; i < newShip.size; i++)
    {
        if (dir == HORIZONTAL)
        {
            grid[row][col + i] = SHIP;
        }
        else
        { // VERTICAL
            grid[row + i][col] = SHIP;
        }
    }

    // 4. UPDATE SHIP DETAILS: Save its location and add it to our vector list
    newShip.startRow = row;
    newShip.startCol = col;
    newShip.orientation = dir;
    ships.push_back(newShip);

    return true;
}

bool Board::receiveAttack(int row, int col)
{
    // Ensure that click is on board first
    if (row < 0 || row >= 10 || col < 0 || col >= 10)
        return false;

    CellState currentState = grid[row][col];
    char rowLetter = 'A' + row;
    int colNumber = col + 1;

    if (currentState == SHIP)
    {
        grid[row][col] = HIT;
        std::cout << "Attack at " << rowLetter << colNumber << " - HIT!\n";

        for (int i = 0; i < ships.size(); i++)
        {
            Ship &s = ships[i];
            bool shipFound = false;

            if (s.orientation == HORIZONTAL)
            {
                if (row == s.startRow && col >= s.startCol && col < s.startCol + s.size)
                {
                    shipFound = true;
                }
            }
            else
            { // VERTICAL
                if (col == s.startCol && row >= s.startRow && row < s.startRow + s.size)
                {
                    shipFound = true;
                }
            }

            if (shipFound)
            {
                s.takeHit();
                if (s.isSunk())
                {
                    std::string shipName = "Ship";
                    if (s.size == 5) shipName = "Carrier";
                    else if (s.size == 4) shipName = "Battleship";
                    else if (s.size == 3) shipName = "Cruiser/Submarine";
                    else if (s.size == 2) shipName = "Destroyer";

                    std::cout << "*** You sunk a " << shipName << "! ***\n";
                }
                break;
            }
        }
        return true;
    }
    else if (currentState == EMPTY)
    {
        grid[row][col] = MISS;
        std::cout << "Attack at " << rowLetter << colNumber << " - MISS.\n";
        return true;
    }

    return false;
}

bool Board::allShipsSunk()
{
    for (int i = 0; i < ships.size(); i++)
    {
        if (!ships[i].isSunk())
        {
            return false;
        }
    }
    return true;
}

void Board::markCell(int row, int col, const std::string& status)
{
    if (row < 0 || row >= 10 || col < 0 || col >= 10) return;

    if (status == "HIT")
    {
        grid[row][col] = HIT;
        std::cout << "[Network] Marked HIT at row " << row << ", col " << col << "\n";
    }
    else if (status == "MISS")
    {
        grid[row][col] = MISS;
        std::cout << "[Network] Marked MISS at row " << row << ", col " << col << "\n";
    }
}

bool Board::isAlreadyGuessed(int row, int col)
{
    if (row < 0 || row >= 10 || col < 0 || col >= 10) return true;
    return (grid[row][col] == HIT || grid[row][col] == MISS);
}

void Board::draw(int offsetX, int offsetY, bool hideShips)
{
    for (int row = 0; row < 10; row++)
    {
        for (int col = 0; col < 10; col++)
        {
            int x = offsetX + (col * CELL_SIZE);
            int y = offsetY + (row * CELL_SIZE);

            CellState currentState = grid[row][col];

            if (currentState == SHIP && !hideShips)
            {
                DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, DARKGRAY);
            }
            else
            {
                DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, { 41, 128, 185, 255 });
            }

            DrawRectangleLines(x, y, CELL_SIZE, CELL_SIZE, BLACK);

            int centerX = x + (CELL_SIZE / 2);
            int centerY = y + (CELL_SIZE / 2);
            float radius = CELL_SIZE * 0.3f;

            if (currentState == HIT)
            {
                DrawCircle(centerX, centerY, radius, RED);
            }
            else if (currentState == MISS)
            {
                DrawCircle(centerX, centerY, radius, WHITE);
            }
        }
    }
}