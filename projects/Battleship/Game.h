#pragma once
#include "raylib.h"
#include "Board.h"
#include "Ship.h"

class Game {
public:
    Board board;
    Ship ship;

    Game();
    ~Game();

    void Draw();
    void Update();
    void getTurn();
    void gameOver();
    void checkFleet();
};