#pragma once
#include "raylib.h"
#include <deque>

class Snake
{
public:
    std::deque<Vector2> body;
    Vector2 direction;
    bool AddSegment;
    Color color; // Need multiple colors for multiplayer

    std::deque<Vector2> initialBody;
    Vector2 initialDirection;

    // Custom constructor
    Snake(std::deque<Vector2> startBody, Vector2 startDir, Color c);

    Snake();
    void Draw();
    void Update();
    void Reset();

    bool HandleInput(int upKey, int downKey, int leftKey, int rightKey);
};