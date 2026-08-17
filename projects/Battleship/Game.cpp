#include "Game.h"
#include "Globals.h"
#include "raymath.h"
#include "Board.h"
#include "Player.h"
#include <iostream>

// Game class is referee/ manager
// Holds pboth players
// Keeps track of turns
// manages state machine (setup, playing, game over)
// checks for wins

// Constructor: Set up the human (false) and enemy (true), and start in PLACEMENT
Game::Game() : human(false), enemy(true)
{
    state = PLACEMENT;
    humanWon = false;

    // Load ship queue
    shipsToPlace = {5, 4, 3, 3, 2};
    currentShipIndex = 0;
    currentOrientation = HORIZONTAL;
}

void Game::handleInput(int row, int col)
{
    if (state == PLACEMENT)
    {
        int currentSize = shipsToPlace[currentShipIndex]; // retrieve size of current ship to be placed
        Ship newShip(currentSize);                        // create a new ship object of the currentSize

        bool success = human.board.placeShip(newShip, row, col, currentOrientation);

        if (success)
        {
            currentShipIndex++; // move to next ship

            if (currentShipIndex >= shipsToPlace.size())
            {
                enemy.autoPlaceShips(shipsToPlace); // place enemy ships randomly

                state = PLAYER_TURN; // switch to player turn
            }
        }
    }
    else if (state == PLAYER_TURN)
    {
        // 1. Attack the enemy board
        bool attacked = enemy.board.receiveAttack(row, col);

        // 2. If it was a valid new click, end turn and let enemy go
        if (attacked)
        {
            state = ENEMY_TURN;
        }
    }
}

void Game::update()
{
    // Only check for wins or AI moves if we are actually playing the game!
    if (state == PLAYER_TURN || state == ENEMY_TURN)
    {

        // Check for wins
        if (enemy.board.allShipsSunk())
        { // Make sure this matches your exact method name
            humanWon = true;
            state = GAME_OVER;
        }
        else if (human.board.allShipsSunk())
        {
            humanWon = false;
            state = GAME_OVER;
        }

        // Handle the computer's turn
        if (state == ENEMY_TURN)
        {
            // Add the time elapsed since the last frame
            aiTimer += GetFrameTime();

            // Wait 1 second (1.0f) before letting the AI move
            if (aiTimer >= 1.0f)
            {
                enemy.performAIMove(human.board);

                // Reset the timer and give control back to the player
                aiTimer = 0.0f;
                state = PLAYER_TURN;
            }
        }
    }
}

void Game::rotateShip()
{
    if (currentOrientation == HORIZONTAL)
    {
        currentOrientation = VERTICAL;
    }
    else
    {
        currentOrientation = HORIZONTAL;
    }
}
