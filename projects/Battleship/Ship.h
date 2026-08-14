#pragma once
#include "Globals.h"

class Ship {
public:
    int size;
    int hits;
    int startRow;
    int startCol;

    Orientation orientation;

    Ship();
    Ship(int shipSize);
    bool isSunk();
    void takeHit();
    void drawShip();
};