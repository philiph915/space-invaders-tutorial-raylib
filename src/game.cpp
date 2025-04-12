#include "game.h"
#include <iostream>


Game::Game()
{
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    aliensDirection = 1;
    timeLastAlienFired = 0;
    timeLastSpawn = 0;
    mysteryShipSpawnInterval = GetRandomValue(10,20);
}

Game::~Game()
{
    Alien::UnloadImages();
}

void Game::Draw()
{
    spaceship.Draw();

    // Automatically draw all the lasers in the player ships laser array
    for (auto& laser: spaceship.lasers)
    {
        laser.Draw();
    }

    // Automatically draw all the lasers in the alienlasers array
    for (auto& laser: alienLasers)
    {
        laser.Draw();
    }

    // Automatically draw all the obstacles
    for (auto& obstacle: obstacles)
    {
        obstacle.Draw();
    }

    // Automatically draw all the aliens
    for (auto& alien: aliens)
    {
        alien.Draw();
    }

    mysteryship.Draw();
}

void Game::Update()
{

    // Mystery ship spawn logic
    double currentTime = GetTime();
    if (currentTime - timeLastSpawn > mysteryShipSpawnInterval)
    {
        mysteryship.Spawn();
        timeLastSpawn = GetTime();
        mysteryShipSpawnInterval = GetRandomValue(10,20);
    }

    // Automatically update all the lasers in the player ships laser array
    for (auto& laser: spaceship.lasers)
    {
        laser.Update();

        DeleteInactiveLasers();
        // std::cout << "Vector Size: " << spaceship.lasers.size() << std::endl; //debuigging: test if lasers are being deleted
    }
    MoveAliens();
    AlienShootLaser();
    for (auto& laser: alienLasers)
    {
        laser.Update();
    }

    // Move the mystery ship
    mysteryship.Update();
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
    // delete lasers from player laser array
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

    // delete lasers from alienLasers array
    for (auto it = alienLasers.begin(); it != alienLasers.end();)
    {
        if(!it -> active)
        {
            it = alienLasers.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

std::vector<Obstacle> Game::CreateObstacles()
{
    int obstacleWidth = Obstacle::grid[0].size()*3;
    float gap = (GetScreenWidth() - 4*obstacleWidth)/5;

    for (int i = 0; i < 4; i++)
    {
        float offsetX = (i + 1) * gap + i * obstacleWidth;
        obstacles.push_back(Obstacle({offsetX,float(GetScreenHeight() - 100)}));
    }
    return obstacles;
}

std::vector<Alien> Game::CreateAliens()
{
    std::vector<Alien> aliens;
    for (int row=0; row < 5; row++) 
    {
        for (int column = 0; column < 11; column++)
        {
            // Assign the alien position based on row / col
            float x = column * 55 + 75;
            float y = row * 55 + 110;

            // Assign alien type based on row
            int alienType;
            if (row == 0) {
                alienType = 3;
            }
            else if (row==1 || row==2) {
                alienType = 2;
            }
            else{
                alienType = 1;
            }

            // Add the alien to the aliens array
            aliens.push_back(Alien(alienType,{x,y}));
        }
    }
    return aliens;
}

void Game::MoveAliens()
{
    for (auto& alien: aliens)
    {
        if(alien.position.x + alien.alienImages[alien.type-1].width > GetScreenWidth())
        {
            aliensDirection=-1;
            MoveDownAliens(4);
        }
        if (alien.position.x < 0)
        {
            aliensDirection = 1;
            MoveDownAliens(4);
        }
        alien.Update(aliensDirection);
    }
}

void Game::MoveDownAliens(int distance)
{
    for (auto& alien: aliens)
    {
        alien.position.y += distance;
    }
}

void Game::AlienShootLaser()
{
    double currentTime = GetTime(); // time since game started
    if (currentTime - timeLastAlienFired >= alienLaserShootInterval && !aliens.empty() )
    {
        // select a random alien and make it shoot a laser
        int randomIndex = GetRandomValue(0,aliens.size()-1);
        Alien& alien = aliens[randomIndex]; // get a reference to the alien at randomIndex
        alienLasers.push_back(Laser({alien.position.x + alien.alienImages[alien.type-1].width/2, 
                                    alien.position.y + alien.alienImages[alien.type-1].height},6));
    timeLastAlienFired = GetTime();
    }
}
