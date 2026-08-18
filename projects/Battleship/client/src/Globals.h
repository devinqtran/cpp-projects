#pragma once

enum GameState
{
    CONNECTING,
    WAITING_FOR_OPPONENT,
    PLACEMENT,
    PLAYER_TURN,
    ENEMY_TURN,
    GAME_OVER
};

enum Orientation
{
    HORIZONTAL,
    VERTICAL
};

enum CellState
{
    EMPTY,
    SHIP,
    HIT,
    MISS
};