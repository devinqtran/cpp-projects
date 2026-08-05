#include "raylib.h"
#include "Game.h"
#include "Globals.h"

int main()
{
    InitWindow(2 * offset + cellSize * cellCount, 2 * offset + cellSize * cellCount, "Retro Snake: Versus");
    SetTargetFPS(60);

    Game game = Game();

    while (!WindowShouldClose())
    {
        if (eventTriggered(0.2))
        {
            game.Update();
        }

        // Player 1 uses WASD
        if (game.snake1.HandleInput(KEY_W, KEY_S, KEY_A, KEY_D))
        {
            game.running = true;
            game.winner = 0;
        }

        // Player 2 uses ARROWS
        if (game.snake2.HandleInput(KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT))
        {
            game.running = true;
            game.winner = 0;
        }

        BeginDrawing();
        ClearBackground(green);

        DrawText("Retro Snake: Versus", offset - 5, 20, 40, darkGreen);

        // Draw Player 1 Score (Left)
        DrawText(TextFormat("P1: %i", game.score1), offset - 5, offset + cellSize * cellCount + 10, 40, darkGreen);
        // Draw Player 2 Score (Right)
        DrawText(TextFormat("P2: %i", game.score2), offset - 5 + (cellSize * cellCount) - 100, offset + cellSize * cellCount + 10, 40, BLUE);

        game.Draw();

        DrawRectangleLinesEx(Rectangle{(float)offset - 5, (float)offset - 5, (float)cellSize * cellCount + 10, (float)cellSize * cellCount + 10}, 5, darkGreen);

        if (!game.running && game.winner > 0)
        {
            const char *winText = "";
            Color winColor = BLACK;

            if (game.winner == 1)
            {
                winText = "Player 1 Wins!";
                winColor = darkGreen;
            }
            else if (game.winner == 2)
            {
                winText = "Player 2 Wins!";
                winColor = BLUE;
            }
            else if (game.winner == 3)
            {
                winText = "It's a Tie!";
                winColor = BLACK;
            }

            // Calculate center of the board
            int textWidth = MeasureText(winText, 60);
            int centerX = offset + (cellSize * cellCount) / 2 - textWidth / 2;
            int centerY = offset + (cellSize * cellCount) / 2 - 30;

            DrawText(winText, centerX, centerY, 60, winColor);

            const char *restartText = "Press any movement key to restart";
            int subWidth = MeasureText(restartText, 20);
            DrawText(restartText, offset + (cellSize * cellCount) / 2 - subWidth / 2, centerY + 70, 20, GRAY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}