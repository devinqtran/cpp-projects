#pragma once
#include "raylib.h"
#include <deque>

class Snake
{
public:
    std::deque<Vector2> body;
    Vector2 direction;
    bool AddSegment;

    Snake();
    void Draw();
    void Update();
    void Reset();
};