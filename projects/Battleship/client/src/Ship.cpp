#include "Ship.h"

// Constructor
Ship::Ship(int shipSize) {
    size = shipSize;
    hits = 0;

    // negative shows ship is not on board
    startRow = -1;
    startCol = -1;

    // default orientation
    orientation = HORIZONTAL;

}

bool Ship::isSunk() {
    return hits >= size;
}

void Ship::takeHit() {
    hits++;
}