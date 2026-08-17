#pragma once
#include "Board.h"

// Represents competitor in the gfame
// Hold players board
// Handle logic specific to that player

class Player {
public:
    Board board;
    bool isAI;
};