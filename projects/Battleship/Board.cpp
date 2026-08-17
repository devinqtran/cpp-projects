#include "Board.h"
#include <vector>
#include <iostream> // Don't forget to include this for std::cout!

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

    // Check the current cellState to see if the spot has been guessed
    CellState currentState = grid[row][col];

    // Convert coordinates for terminal output (e.g., Row 0, Col 0 -> A1)
    char rowLetter = 'A' + row;
    int colNumber = col + 1;

    // If the square contains a SHIP
    if (currentState == SHIP)
    {
        grid[row][col] = HIT;

        // Print attack
        std::cout << "Attack at " << rowLetter << colNumber << " - HIT!\n";

        // Loop through our list of ships to find out WHICH one got hit
        for (int i = 0; i < ships.size(); i++)
        {
            Ship &s = ships[i];

            // A boolean to track if we found the ship, so we only write the sinking logic once
            bool shipFound = false;

            // Check if the current row/col falls inside this ship's coordinates
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

            // If this is the ship that got hit, apply the damage and check if it sank
            if (shipFound)
            {
                s.takeHit(); // Apply the damage

                if (s.isSunk())
                {
                    // Figure out the ship's name based on its size
                    std::string shipName = "Ship";
                    if (s.size == 5)
                        shipName = "Carrier";
                    else if (s.size == 4)
                        shipName = "Battleship";
                    else if (s.size == 3)
                        shipName = "Cruiser/Submarine";
                    else if (s.size == 2)
                        shipName = "Destroyer";

                    std::cout << "*** You sunk a " << shipName << "! ***\n";
                }

                break; // We found and processed the ship, no need to keep looping
            }
        }
        return true; // Valid move, turn is over
    }
    // If the square is EMPTY water
    else if (currentState == EMPTY)
    {
        grid[row][col] = MISS;

        // Print attack
        std::cout << "Attack at " << rowLetter << colNumber << " - MISS.\n";

        // Return TRUE so the Game knows this was a valid action and the turn should change!
        return true;
    }

    // If the cell was already a HIT or MISS, return false (invalid move)
    return false;
}

// Check if all the ships have been sunk
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