#include "Game.h"
#include "Globals.h"
#include "raymath.h"
#include "raylib.h"
#include "Board.h"
#include "Player.h"
#include <iostream>

Game::Game() : human(false), enemy(true)
{
    state = GameState::CONNECTING;
    gameStatusText = "Connecting to server...";

    shipsToPlace = {5, 4, 3, 3, 2};
    currentShipIndex = 0;
    currentOrientation = Orientation::HORIZONTAL; // Ensure this matches your Globals.h enum

    // Connect to the local server in the background
    if (network.connect("127.0.0.1", "8080")) {
        // We stay in CONNECTING until the server tells us what to do.
    } else {
        gameStatusText = "Connection failed. Please restart the game.";
    }
}

void Game::update()
{
    // Process all pending messages from the server
    while (network.has_message()) {
        Protocol::Message msg = network.pop_message();
        handleNetworkMessage(msg);
    }
}

void Game::handleNetworkMessage(const Protocol::Message& msg) {
    switch (msg.type) {
        case Protocol::CommandType::WAITING:
            state = GameState::WAITING_FOR_OPPONENT;
            gameStatusText = "Waiting for an opponent to join...";
            break;

        case Protocol::CommandType::MATCHED:
            if (currentShipIndex < shipsToPlace.size()) {
                state = GameState::PLACEMENT;
                gameStatusText = "Opponent found! Place your ships.";
            } else {
                gameStatusText = "Both players ready. Game starting!";
            }
            break;

        case Protocol::CommandType::YOURTURN:
            state = GameState::PLAYER_TURN;
            gameStatusText = "Your Turn! Click the enemy board to fire.";
            break;

        case Protocol::CommandType::RESULT:
            if (state == GameState::PLAYER_TURN) {
                // The server confirmed OUR shot. 
                // TODO: You will need a way to mark the enemy tracking board purely 
                // visually based on msg.status ("HIT" or "MISS").
                // e.g., enemy.board.markVisualCell(msg.row, msg.col, msg.status);

                state = GameState::ENEMY_TURN;
                gameStatusText = "Opponent's turn...";
            } else {
                // The opponent shot at US. The server is telling us where they hit.
                // We update our own board visually.
                human.board.receiveAttack(msg.row, msg.col); 
            }
            break;

        case Protocol::CommandType::GAMEOVER:
            state = GameState::GAME_OVER;
            if (msg.status == "WIN") {
                gameStatusText = "VICTORY! You sank the enemy fleet!";
            } else {
                gameStatusText = "DEFEAT. Your fleet was destroyed.";
            }
            break;

        default:
            break;
    }
}

void Game::handleInput(int row, int col)
{
    // Prevent out-of-bounds clicks
    if (row < 0 || row > 9 || col < 0 || col > 9) return;

    if (state == GameState::PLACEMENT)
    {
        int currentSize = shipsToPlace[currentShipIndex];
        Ship newShip(currentSize); 

        // 1. Try to place the ship locally on our own screen
        bool success = human.board.placeShip(newShip, row, col, currentOrientation);

        if (success)
        {
            // 2. Tell the server we placed it
            char dirChar = (currentOrientation == Orientation::HORIZONTAL) ? 'H' : 'V';
            std::string networkMsg = Protocol::buildPlace(row, col, dirChar);
            network.send(networkMsg);

            currentShipIndex++;

            // 3. Wait for the opponent if we are done
            if (currentShipIndex >= shipsToPlace.size())
            {
                state = GameState::WAITING_FOR_OPPONENT;
                gameStatusText = "Waiting for opponent to finish placing ships...";
            }
        }
    }
    else if (state == GameState::PLAYER_TURN)
    {
        // Ask the server to validate our attack
        std::string networkMsg = Protocol::buildAttack(row, col);
        network.send(networkMsg);
        
        // We do NOT change state or update the board here! 
        // We stay in PLAYER_TURN until the server replies with a RESULT message.
    }
}

void Game::rotateShip()
{
    if (currentOrientation == Orientation::HORIZONTAL)
    {
        currentOrientation = Orientation::VERTICAL;
    }
    else
    {
        currentOrientation = Orientation::HORIZONTAL;
    }
}

void Game::draw() {
    ClearBackground(RAYWHITE);

    // Draw our board on the left (50 pixels from the edge). 
    // hideShips = false so we can see our own fleet.
    human.board.draw(50, 50, false); 

    // Draw the enemy board on the right (600 pixels from the edge).
    // hideShips = true so we don't peek at their ships!
    enemy.board.draw(600, 50, true);

    // Draw the current network/game status message at the bottom
    DrawText(gameStatusText.c_str(), 50, 500, 20, DARKGRAY);
    
    // Optional: Draw a "preview" of the ship we are currently placing
    if (state == GameState::PLACEMENT && currentShipIndex < shipsToPlace.size()) {
        std::string placementText = "Placing Ship Size: " + std::to_string(shipsToPlace[currentShipIndex]);
        DrawText(placementText.c_str(), 50, 550, 20, BLUE);
        DrawText("Press 'R' to rotate", 50, 580, 20, GRAY);
    }
}