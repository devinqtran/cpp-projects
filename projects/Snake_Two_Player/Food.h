#pragma once
#include "raylib.h"
#include <deque>

class Food
{
public:
    Vector2 position;
    Texture2D texture;

    Food(std::deque<Vector2> snake1Body, std::deque<Vector2> snake2Body);
    ~Food();

    void Draw();
    Vector2 GenerateRandomCell();
    Vector2 GenerateRandomPos(std::deque<Vector2> snake1Body, std::deque<Vector2> snake2Body);
};