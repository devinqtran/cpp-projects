#pragma once
#include "Player.h"
#include "Globals.h"

class Game {
public:
    Player human;
    Player enemy;
    GameState state;
    bool humanWon;

    Game();

    // main.cpp will pass mouse clicks into this function
    void handleInput(int row, int col); 
    
    // Updates game logic (like checking for wins or telling the AI to move)
    void update(); 
};