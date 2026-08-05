#pragma once
#include "raylib.h"
#include <deque>

// Define constants here
extern Color red;
extern Color green;
extern Color darkGreen;

extern int cellSize;
extern int cellCount;
extern int offset;

// Helper function declarations
bool eventTriggered(double interval);
bool ElementInDeque(Vector2 element, std::deque<Vector2> deque);