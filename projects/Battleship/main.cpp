#include "raylib.h"
#include "Globals.h"
#include "Board.h"
#include "Game.h"
#include <iostream>
#include <ctime>

// Pass game object by reference
void drawBoard(Game& myGame) {
    bool isPlacingShips = (myGame.state == 0);

    // Draw border
    DrawRectangleLinesEx(Rectangle{(float)offset - 5, (float)offset - 5, (float)cellSize * gridCount + 10, (float)cellSize * gridCount + 10}, 5, navy);

    // Draw grid
    for (int i = 0; i <= gridCount; i++)
    {
        int linePos = offset + (i * cellSize);

        // Vertical x change
        DrawLine(linePos, offset, linePos, boardEnd, navy);

        // Horizontal lines (start at X=offset, go right to X=boardEnd)
        DrawLine(offset, linePos, boardEnd, linePos, navy);
    }

    // Loop for checking cell state
    for (int row = 0; row < 10; row++)
    {
        for (int col = 0; col < 10; col++)
        {
            // Find the top-left corner of the current cell for drawing
            int cellX = offset + (col * cellSize);
            int cellY = offset + (row * cellSize);

            // Find the center of the cell for drawing circles (pegs)
            int centerX = cellX + (cellSize / 2);
            int centerY = cellY + (cellSize / 2);

            // 3. Choose which board to read from based on the game state
            CellState state;
            if (isPlacingShips) {
                state = myGame.human.board.getCellState(row, col);
            } else {
                state = myGame.enemy.board.getCellState(row, col);
            }

            // 4. Draw the cell based on the state
            if (state == SHIP)
            {
                // Only draw the gray rectangle if we are looking at the player's board
                // This keeps the enemy board "blank" by hiding un-hit ships
                if (isPlacingShips) {
                    DrawRectangle(cellX + 2, cellY + 2, cellSize - 4, cellSize - 4, GRAY);
                }
            }
            else if (state == HIT)
            {
                // Draw a red peg
                DrawCircle(centerX, centerY, cellSize / 3, RED);
            }
            else if (state == MISS)
            {
                // Draw a white peg
                DrawCircle(centerX, centerY, cellSize / 3, WHITE);
            }
        }
    }
}

int main()
{
    // Seed the random number generator so the AI behaves differently every game
    srand(time(NULL));

    InitWindow(1200, 1000, "Battleship");

    SetTargetFPS(60);

    // Create board
    Game myGame;
    
    while (!WindowShouldClose())
    {
        // Mouse input logic
        // Check if the Left Mouse Button was clicked this frame
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            int mouseX = GetMouseX();
            int mouseY = GetMouseY();

            // We don't want to register clicks in the 50px border!
            if (mouseX >= offset && mouseX < boardEnd &&
                mouseY >= offset && mouseY < boardEnd)
            {

                // 2. CONVERT PIXELS TO GRID:
                // Subtract the border offset, then divide by the size of the cells
                int col = (mouseX - offset) / cellSize;
                int row = (mouseY - offset) / cellSize;

                // DEBUG
                std::cout << "Attempting to place ship at Row: " << row << ", Col: " << col << "\n";
                std::cout << "Current state: " << myGame.state << "\n";


                // 3. SEND ATTACK:
                myGame.handleInput(row, col);
            }
        }

        // Check for right-click to rotate ships
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            myGame.rotateShip();
        }

        myGame.update();

        BeginDrawing();
        ClearBackground(water);

        DrawText("Battleship", 15, 15, 25, navy);

        drawBoard(myGame);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}