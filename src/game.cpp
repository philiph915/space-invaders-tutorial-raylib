#include "game.h"
#include <iostream>


Game::Game()
{
}

Game::~Game()
{
}

void Game::Draw()
{
    spaceship.Draw();

    // Automatically draw all the lasers in the player ships laser array
    for (auto& laser: spaceship.lasers)
    {
        laser.Draw();
    }
}

void Game::Update()
{
    // Automatically update all the lasers in the player ships laser array
    for (auto& laser: spaceship.lasers)
    {
        laser.Update();

        DeleteInactiveLasers();
        // std::cout << "Vector Size: " << spaceship.lasers.size() << std::endl; //debuigging: test if lasers are being deleted
    }
}

void Game::HandleInput()
{
    // Use IsKeyDown for key being continuously held down
    if(IsKeyDown(KEY_LEFT))
    {
        spaceship.MoveLeft();
    } 
    else if (IsKeyDown(KEY_RIGHT))
    {
        spaceship.MoveRight();
    }
    
    if(IsKeyDown(KEY_SPACE))
    {
        spaceship.FireLaser();
    }

    // Use IsKeyPressed for instantaneous button press
}


// Using an iterator loop allows you to dynamically delete an array without causing errors due to the indexes changing
// the key is in the it = spaceship.lasers.erase(it), as this returns a new valid index and allows you to proceed
// In pygame, we had to create a copy of the laser array, build that up, the replace the original array once we
// finished iterating over it.
void Game::DeleteInactiveLasers()
{
    for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();)
    {
        if(!it -> active)
        {
            it = spaceship.lasers.erase(it);
        }
        else
        {
            ++it;
        }
    }
}
