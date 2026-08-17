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