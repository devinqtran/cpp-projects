#include "Globals.h"
#include "raymath.h"

Color water = {3, 165, 252, 255};
Color navy = {11, 0, 79, 255};
Color metal = {105, 105, 105, 255};

int offset = 50;
int cellSize = 90;
int gridCount = 10;
int boardEnd = offset + (gridCount * cellSize);