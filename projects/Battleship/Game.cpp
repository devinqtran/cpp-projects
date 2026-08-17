#include "Game.h"
#include "Globals.h"
#include "raymath.h"

// Game class is referee/ manager
// Holds pboth players
// Keeps track of turns
// manages state machine (setup, playing, game over)
// checks for wins

// Constructor
Game::Game() : 