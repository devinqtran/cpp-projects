#include "Player.h"
#include <cstdlib> // For random numbers

Player::Player(bool isComputer) {
    isAI = isComputer;
}

void Player::performAIMove(Board& enemyBoard) {
    if (!isAI) return; // Safety check

    bool validMove = false;
    while (!validMove) {
        // Pick a random row and col from 0 to 9
        int row = rand() % 10;
        int col = rand() % 10;

        // Check if we already attacked here
        CellState targetCell = enemyBoard.getCellState(row, col);
        if (targetCell != HIT && targetCell != MISS) {
            // It's a valid spot! Fire the attack.
            enemyBoard.receiveAttack(row, col);
            validMove = true;
        }
    }
}

void Player::autoPlaceShips(std::vector<int> shipSizes) {
    for (int i = 0; i < shipSizes.size(); i++) {
        int currentSize = shipSizes[i];
        bool placed = false;

        // Keep trying random spots until it fits
        while (!placed) {
            int row = rand() % 10;
            int col = rand() % 10;
            
            // rand() % 2 returns either 0 or 1. 
            // Ternary operator (?) to turn that into HORIZONTAL or VERTICAL
            Orientation dir = (rand() % 2 == 0) ? HORIZONTAL : VERTICAL;

            Ship newShip(currentSize);
            
            // If it's a valid spot, placeShip returns true breaking while loop
            placed = board.placeShip(newShip, row, col, dir);
        }
    }
}