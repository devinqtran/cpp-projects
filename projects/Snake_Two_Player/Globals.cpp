#include "Globals.h"
#include "raymath.h"
#include <deque>

Color red = {255, 0, 0, 255};
Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};
Color lightTan = {252, 250, 246, 255};
Color blue = {52, 177, 235, 255};

int cellSize = 30;
int cellCount = 25;
int offset = 75;

double lastUpdateTime = 0;

bool eventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

bool ElementInDeque(Vector2 element, std::deque<Vector2> deque)
{
    for (unsigned int i = 0; i < deque.size(); i++)
    {
        if (Vector2Equals(deque[i], element))
        {
            return true;
        }
    }
    return false;
}