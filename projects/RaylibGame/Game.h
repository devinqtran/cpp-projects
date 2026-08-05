#pragma once
#include "Snake.h"
#include "Food.h"
#include "raylib.h"

class Game
{
public:
    Snake snake;
    Food food;
    bool running;
    int score;
    Sound eatSound;
    Sound wallSound;

    Game();
    ~Game();

    void Draw();
    void Update();
    void CheckCollisionWithFood();
    void CheckCollisionWithEdges();
    void CheckCollisionWithTail();
    void GameOver();
};