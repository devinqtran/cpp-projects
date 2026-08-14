#pragma once
#include "raylib.h"

enum CellState {
    EMPTY = 0,
    SHIP,
    HIT,
    MISS
};

enum Orientation {
    HORIZONTAL,
    Vertical
};

extern Color water;
extern Color navy;
extern Color metal;

extern int offset;
extern int cellSize;
extern int gridCount;
extern int boardEnd;