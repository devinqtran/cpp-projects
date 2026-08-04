#include "raylib.h"

using namespace std;

Color red = {255, 0, 0, 255};
Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 30;
int cellCount = 25;

class Food
{
public:
    Vector2 position;
    Texture2D texture;

    // Food Constructor
    Food()
    {
        Image image = LoadImage("graphics/food.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = GenerateRandomPos();
    }

    // Destructor
    ~Food()
    {
        UnloadTexture(texture);
    }

    void Draw()
    {
        DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE);
    }

    Vector2 GenerateRandomPos()
    {
        float x = GetRandomValue(0, cellCount - 1);
        float y = GetRandomValue(0, cellCount - 1);
        return Vector2{x, y};
    }
};

int main()
{
    // Initialization
    InitWindow(cellSize * cellCount, cellSize * cellCount, "Retro Snake");
    SetTargetFPS(60);

    Food food = Food();

    // Main game loop
    while (!WindowShouldClose())
    {
        // Draw
        BeginDrawing();
        ClearBackground(green);
        food.Draw();
        DrawText("Raylib is working in C++!", 250, 200, 20, DARKGRAY);
        // DrawCircle(200, 200, 20, darkGreen);
        EndDrawing();
    }

    // De-Initialization
    CloseWindow();
    return 0;
}