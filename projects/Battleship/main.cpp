#include "raylib.h"
#include "Globals.h"

int main()
{
    InitWindow(1000, 1000, "Battleship");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(water);

        DrawText("Battleship", 15, 15, 25, navy);

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

        EndDrawing();
    }
    CloseWindow();
    return 0;
}