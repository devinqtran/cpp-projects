#include "raylib.h"
#include "Game.h"
#include "Globals.h"

int main()
{
    InitWindow(2 * offset + cellSize * cellCount, 2 * offset + cellSize * cellCount, "Retro Snake");
    SetTargetFPS(60);

    Game game = Game();

    while (!WindowShouldClose())
    {
        // Update Game State
        if (eventTriggered(0.2))
        {
            game.Update();
        }

        // Input handling
        if (game.snake.HandleInput(KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT))
        {
            game.running = true;
        }

        // Draw
        BeginDrawing();
        ClearBackground(green);

        DrawText("Retro Snake", offset - 5, 20, 40, darkGreen);
        DrawText(TextFormat("%i", game.score), offset - 5, offset + cellSize * cellCount + 10, 40, darkGreen);

        game.Draw();

        DrawRectangleLinesEx(Rectangle{(float)offset - 5, (float)offset - 5, (float)cellSize * cellCount + 10, (float)cellSize * cellCount + 10}, 5, darkGreen);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}