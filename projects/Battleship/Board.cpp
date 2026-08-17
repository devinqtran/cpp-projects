#include "Board.h"
#include <vector>

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
    fleet.push_back(newShip);

    return true;
}

bool Board::receiveAttack(int row, int col)
{
    // Ensure that click is on board
    if (row < 0 || row >= 10 || col < 0 || col >= 10)
        return false;

    // If the square contains a SHIP
    if (grid[row][col] == SHIP)
    {
        grid[row][col] = HIT;

        // Loop through our list of ships to find out WHICH one got hit
        for (int i = 0; i < fleet.size(); i++)
        {

            // We use a reference (&) so we modify the actual ship in the vector, not a copy
            Ship &s = fleet[i];

            // Check if the current row/col falls inside this ship's coordinates
            if (s.orientation == HORIZONTAL)
            {
                if (row == s.startRow && col >= s.startCol && col < s.startCol + s.size)
                {
                    s.takeHit();
                    break; // We found the ship, no need to keep looping
                }
            }
            else
            { // VERTICAL
                if (col == s.startCol && row >= s.startRow && row < s.startRow + s.size)
                {
                    s.takeHit();
                    break;
                }
            }
        }
        return true;
    }
    // If the square is EMPTY water
    else if (grid[row][col] == EMPTY)
    {
        grid[row][col] = MISS;
        return false;
    }

    // If the cell was already a HIT or MISS, return false
    return false;
}

// Check if all the ships have been sunk
bool allShipsSunk() {
    for (int i = 0; i < ships.size() - 1; i++) {
        if (!ships[i].isSunk()) {
            return false;
        }
    }
    return true;
}