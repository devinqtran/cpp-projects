#pragma once
#include "Snake.h"
#include "Food.h"
#include "raylib.h"

class Game
{
public:
    Snake snake1;
    Snake snake2;
    Food food;

    bool running;
    int score1;
    int score2;
    int winner; // NEW: 0 = None, 1 = P1, 2 = P2, 3 = Tie
    Sound eatSound;
    Sound wallSound;

    Game();
    ~Game();

    void Draw();
    void Update();
    void CheckCollisionWithFood();
    void CheckCollisionWithEdges();
    void CheckCollisionWithTail();
    void GameOver(int deadPlayer);
};