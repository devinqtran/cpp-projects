#pragma once
#include "Player.h"
#include "Globals.h"
#include "NetworkClient.h"
#include <vector>
#include <string>

class Game {
private:
    NetworkClient network; // The background network engine
    
    // Helper to process incoming messages from the server
    void handleNetworkMessage(const Protocol::Message& msg); 

public:
    Player human;
    Player enemy;
    GameState state;

    std::string gameStatusText; // Used to show messages like "Waiting for opponent..."

    std::vector<int> shipsToPlace;
    int currentShipIndex;
    Orientation currentOrientation;

    Game();

    // main.cpp will pass mouse clicks into this function
    void handleInput(int row, int col); 
    
    // Checks the network mailbox and updates the game state
    void update(); 

    void rotateShip();

    void draw();
};