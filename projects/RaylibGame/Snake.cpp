#include "Snake.h"
#include "Globals.h"
#include "raymath.h"

Snake::Snake()
{
    body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    direction = {1, 0};
    AddSegment = false;
}

void Snake::Draw()
{
    for (unsigned int i = 0; i < body.size(); i++)
    {
        float x = body[i].x;
        float y = body[i].y;

        Rectangle segment = Rectangle{(float)offset + x * cellSize, (float)offset + y * cellSize, (float)cellSize, (float)cellSize};
        DrawRectangleRounded(segment, 0.5, 6, darkGreen);
    }
}

void Snake::Update()
{
    body.push_front(Vector2Add(body[0], direction));
    if (AddSegment == true)
    {
        AddSegment = false;
    }
    else
    {
        body.pop_back();
    }
}

void Snake::Reset()
{
    body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    direction = {1, 0};
}

bool Snake::HandleInput(int upKey, int downKey, int leftKey, int rightKey)
{
    bool keyPressed = false;

    if (IsKeyPressed(upKey) && direction.y != 1) {
        direction = {0, -1};
        keyPressed = true;
    }
    if (IsKeyPressed(downKey) && direction.y != -1) {
        direction = {0, 1};
        keyPressed = true;
    }
    if (IsKeyPressed(leftKey) && direction.x != 1) {
        direction = {-1, 0};
        keyPressed = true;
    }
    if (IsKeyPressed(rightKey) && direction.x != -1) {
        direction = {1, 0};
        keyPressed = true;
    }

    return keyPressed;
}