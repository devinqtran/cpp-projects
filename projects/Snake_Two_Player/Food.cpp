#include "Food.h"
#include "Globals.h"
#include "raymath.h"

Food::Food(std::deque<Vector2> snake1Body, std::deque<Vector2> snake2Body)
{
    Image image = LoadImage("graphics/food.png");
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
    position = GenerateRandomPos(snake1Body, snake2Body);
}

Food::~Food()
{
    UnloadTexture(texture);
}

void Food::Draw()
{
    DrawTexture(texture, offset + position.x * cellSize, offset + position.y * cellSize, WHITE);
}

Vector2 Food::GenerateRandomCell()
{
    float x = GetRandomValue(0, cellCount - 1);
    float y = GetRandomValue(0, cellCount - 1);
    return Vector2{x, y};
}

Vector2 Food::GenerateRandomPos(std::deque<Vector2> snake1Body, std::deque<Vector2> snake2Body)
{
    Vector2 pos = GenerateRandomCell();
    while (ElementInDeque(pos, snake1Body) || ElementInDeque(pos, snake2Body))
    {
        pos = GenerateRandomCell();
    }
    return pos;
}