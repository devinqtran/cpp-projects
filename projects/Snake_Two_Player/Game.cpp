#include "Game.h"
#include "Globals.h"
#include "raymath.h"

Game::Game() : 
    snake1({Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}}, {1, 0}, darkGreen),
    snake2({Vector2{6, 15}, Vector2{5, 15}, Vector2{4, 15}}, {1, 0}, BLUE),
    food(snake1.body, snake2.body)
{
    InitAudioDevice();
    eatSound = LoadSound("sounds/eat.mp3");
    wallSound = LoadSound("sounds/wall.mp3");
    running = true;
    score1 = 0;
    score2 = 0;
    winner = 0;
}

Game::~Game()
{
    UnloadSound(eatSound);
    UnloadSound(wallSound);
    CloseAudioDevice();
}

void Game::Draw()
{
    food.Draw();
    snake1.Draw();
    snake2.Draw();
}

void Game::Update()
{
    if (running)
    {
        snake1.Update();
        snake2.Update();
        CheckCollisionWithFood();
        CheckCollisionWithEdges();
        CheckCollisionWithTail();
    }
}

void Game::CheckCollisionWithFood()
{
    if (Vector2Equals(snake1.body[0], food.position))
    {
        food.position = food.GenerateRandomPos(snake1.body, snake2.body);
        snake1.AddSegment = true;
        score1++;
        PlaySound(eatSound);
    }
    else if (Vector2Equals(snake2.body[0], food.position))
    {
        food.position = food.GenerateRandomPos(snake1.body, snake2.body);
        snake2.AddSegment = true;
        score2++;
        PlaySound(eatSound);
    }
}

void Game::CheckCollisionWithEdges()
{
    bool p1Dead = (snake1.body[0].x == cellCount || snake1.body[0].x == -1 || 
                   snake1.body[0].y == cellCount || snake1.body[0].y == -1);
    bool p2Dead = (snake2.body[0].x == cellCount || snake2.body[0].x == -1 || 
                   snake2.body[0].y == cellCount || snake2.body[0].y == -1);

    if (p1Dead && p2Dead) GameOver(3); // Both died at once
    else if (p1Dead) GameOver(1);      // P1 died
    else if (p2Dead) GameOver(2);      // P2 died
}

void Game::CheckCollisionWithTail()
{
    std::deque headlessBody1 = snake1.body;
    headlessBody1.pop_front();
    
    std::deque headlessBody2 = snake2.body;
    headlessBody2.pop_front();

    bool p1Dead = ElementInDeque(snake1.body[0], headlessBody1) || ElementInDeque(snake1.body[0], snake2.body);
    bool p2Dead = ElementInDeque(snake2.body[0], headlessBody2) || ElementInDeque(snake2.body[0], snake1.body);

    if (p1Dead && p2Dead) GameOver(3);
    else if (p1Dead) GameOver(1);
    else if (p2Dead) GameOver(2);
}

void Game::GameOver(int deadPlayer)
{
    // Set the winner based on who died
    if (deadPlayer == 1) winner = 2;
    else if (deadPlayer == 2) winner = 1;
    else winner = 3; // Tie

    snake1.Reset();
    snake2.Reset();
    food.position = food.GenerateRandomPos(snake1.body, snake2.body);
    running = false;
    score1 = 0;
    score2 = 0;
    PlaySound(wallSound);
}