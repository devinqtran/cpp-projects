#include "raylib.h"
#include "Globals.h"
#include "Board.h"
#include "Game.h"
#include <iostream>
#include <string>

int main()
{
    // Initialize the window
    InitWindow(1200, 700, "Battleship - Multiplayer");
    SetTargetFPS(60);

    // Create our game manager (this automatically connects to the server!)
    Game myGame;

    // Define where our two boards will sit on the screen
    const int LEFT_BOARD_X = 50;
    const int RIGHT_BOARD_X = 650;
    const int BOARD_Y = 150;
    const int BOARD_PIXEL_SIZE = Board::CELL_SIZE * 10;

    while (!WindowShouldClose())
    {
        // 1. UPDATE NETWORK & GAME STATE
        myGame.update();

        // 2. HANDLE MOUSE CLICKS
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            int mouseX = GetMouseX();
            int mouseY = GetMouseY();
            
            int activeOffsetX = -1;

            // Figure out WHICH board they should be clicking based on the game state
            if (myGame.state == GameState::PLACEMENT) {
                activeOffsetX = LEFT_BOARD_X; // Place ships on YOUR board
            } 
            else if (myGame.state == GameState::PLAYER_TURN) {
                activeOffsetX = RIGHT_BOARD_X; // Attack the ENEMY board
            }

            // If it's a valid time to click, check if they clicked inside the active board
            if (activeOffsetX != -1) {
                if (mouseX >= activeOffsetX && mouseX < (activeOffsetX + BOARD_PIXEL_SIZE) &&
                    mouseY >= BOARD_Y && mouseY < (BOARD_Y + BOARD_PIXEL_SIZE))
                {
                    // Convert pixels to row/col grid coordinates
                    int col = (mouseX - activeOffsetX) / Board::CELL_SIZE;
                    int row = (mouseY - BOARD_Y) / Board::CELL_SIZE;

                    myGame.handleInput(row, col);
                }
            }
        }

        // Check for right-click to rotate ships during placement
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && myGame.state == GameState::PLACEMENT)
        {
            myGame.rotateShip();
        }

        // Check for Restart
        if (myGame.state == GameState::GAME_OVER) {
            if (IsKeyPressed(KEY_ENTER)) {
                myGame.network.send(Protocol::buildRestart());
            }
        }

        // 3. DRAWING
        BeginDrawing();
        ClearBackground({ 240, 245, 250, 255 }); // Very light blue/gray background

        // Draw Title & Network Status
        DrawText("MULTIPLAYER BATTLESHIP", 50, 30, 40, DARKBLUE);
        DrawText(myGame.gameStatusText.c_str(), 50, 80, 25, RED);

        // Draw Player Board (Left)
        DrawText("YOUR FLEET", LEFT_BOARD_X, BOARD_Y - 30, 20, DARKGRAY);
        myGame.human.board.draw(LEFT_BOARD_X, BOARD_Y, false); // false = show ships

        // Draw Enemy Board (Right)
        DrawText("ENEMY FLEET", RIGHT_BOARD_X, BOARD_Y - 30, 20, DARKGRAY);
        myGame.enemy.board.draw(RIGHT_BOARD_X, BOARD_Y, true); // true = hide ships!

        // Draw Placement Helpers
        if (myGame.state == GameState::PLACEMENT && myGame.currentShipIndex < myGame.shipsToPlace.size()) {
            std::string lengthStr = std::to_string(myGame.shipsToPlace[myGame.currentShipIndex]);
            std::string dirStr = (myGame.currentOrientation == HORIZONTAL) ? "HORIZONTAL" : "VERTICAL";            
            DrawText(("Placing Ship Size: " + lengthStr).c_str(), LEFT_BOARD_X, BOARD_Y + BOARD_PIXEL_SIZE + 20, 20, DARKGRAY);
            DrawText(("Orientation: " + dirStr + " (Right-Click to rotate)").c_str(), LEFT_BOARD_X, BOARD_Y + BOARD_PIXEL_SIZE + 50, 20, GRAY);
        }

        // Draw Game Over instructions
        if (myGame.state == GameState::GAME_OVER) {
            DrawText("Press ENTER to Play Again!", LEFT_BOARD_X + 250, BOARD_Y + BOARD_PIXEL_SIZE + 40, 30, DARKGREEN);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}