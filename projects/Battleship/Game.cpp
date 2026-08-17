#include "Game.h"
#include "Globals.h"
#include "raymath.h"
#include "Board.h"
#include "Player.h"

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
}

void Game::handleInput(int row, int col)
{
    // What a click does depends entirely on the game state!
    if (state == PLACEMENT)
    {
        // (Logic for placing human ships will go here)
        // Once 5 ships are placed, change state to PLAYER_TURN
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
    // Check for wins
    if (enemy.board.allShipsSunk())
    {
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
        // (You might want to add a small Raylib timer here so it doesn't happen instantly!)
        human.performAIMove(human.board); // Note: AI attacks the human's board!
        state = PLAYER_TURN;
    }
}