#include "game.h"
#include <iostream>
#include <fstream>


Game::Game()
{
    InitGame();
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
    if (run==true) {
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
            // DeleteInactiveLasers();
            // std::cout << "Vector Size: " << spaceship.lasers.size() << std::endl; //debuigging: test if lasers are being deleted
        }
        MoveAliens();
        AlienShootLaser();
        for (auto& laser: alienLasers)
        {
            laser.Update();
            // DeleteInactiveLasers();
        }
        
        // Now that all laser objects have been created, delete any that need to be removed
        DeleteInactiveLasers();

        // Move the mystery ship
        mysteryship.Update();

        // Collision detection
        CheckForCollisions();
        
        // User inputs
        HandleInput();
    }
    else
    {
        if (IsKeyPressed(KEY_ENTER))
        {
            Reset();
            InitGame();
        }
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
        obstacles.push_back(Obstacle({offsetX,float(GetScreenHeight() - 200)}));
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
        if(alien.position.x + alien.alienImages[alien.type-1].width > GetScreenWidth()-25)
        {
            aliensDirection=-1;
            MoveDownAliens(4);
        }
        if (alien.position.x < 25)
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

void Game::CheckForCollisions()
{
    // Spaceship lasers 
    for (auto& laser: spaceship.lasers) // automatically defines the range of the for loop and gets every object in spaceship.lasers
    {

        // collision with aliens

        // use an iterator to loop across the  array of alien objects and dynamically delete aliens from the array while iterating over it
        auto it = aliens.begin(); // initialize the iterator at the beginning of the array 
        while (it != aliens.end()) // loop across the array dynamically
        {
            if (CheckCollisionRecs(it -> GetRect(), laser.GetRect())) // calls the GetRect() function of the object that it is pointing to
            {
                it = aliens.erase(it); // if there was a collision, erase the object it points to (this is an alien object)
                laser.active = false; //mark the current laser object for deletion
                // Award points based on which type of alien was hit
                if (it -> type == 1)    {
                    score+=100;
                } else if (it -> type == 2) {
                    score+=200;
                } else if (it -> type == 3) {
                    score+=300;
                }
                CheckHighScore();
            }
            else 
            {
                ++it; //otherwise, continue iterating through the array
            }
        }

        // collision with obstacles
        for (auto& obstacle: obstacles) //automatically gets size of obstacles array and grabs each object
        {
            auto it = obstacle.blocks.begin(); //same logic as before; iterate across array of blocks objects for each obstacle
            while (it != obstacle.blocks.end())
            {
                if (CheckCollisionRecs(it -> GetRect(), laser.GetRect())) // calls the GetRect() function of the object that it is pointing to
                {
                    it = obstacle.blocks.erase(it); // if there was a collision, erase the object block from the obstacle.blocks array
                    laser.active = false; //mark the current laser object for deletion
                }
                else 
                {
                    ++it; //otherwise, continue iterating through the array
                }
            }
        }

        // collision with mystery ship
        if (CheckCollisionRecs(mysteryship.GetRect(),laser.GetRect()))
        {
            mysteryship.alive = false; // this should work because the mystery ship is only collidable while alive (otherwise rect size is 0,0)
            laser.active = false;
            score+=500;
            CheckHighScore();
        }
        
    }

    // Alien lasers
    for (auto& laser: alienLasers)
    {
        // Check collisions with player space ship
        if (CheckCollisionRecs(laser.GetRect(), spaceship.GetRect()))
        {
            laser.active = false;
            std::cout << "Player hit by laser" << std::endl;
            lives--;
            if (lives == 0)
            {
                GameOver();
            }
        }

        // check for collisions with obstacles
        for (auto& obstacle: obstacles) //automatically gets size of obstacles array and grabs each object
        {
            auto it = obstacle.blocks.begin(); //same logic as before; iterate across array of blocks objects for each obstacle
            while (it != obstacle.blocks.end())
            {
                if (CheckCollisionRecs(it -> GetRect(), laser.GetRect())) // calls the GetRect() function of the object that it is pointing to
                {
                    it = obstacle.blocks.erase(it); // if there was a collision, erase the object block from the obstacle.blocks array
                    laser.active = false; //mark the current laser object for deletion
                }
                else 
                {
                    ++it; //otherwise, continue iterating through the array
                }
            }
        }
    }

    // Alien collision with obstacles & player
    for (auto& alien: aliens) { // for every alien, check every obstacle
        for (auto& obstacle: obstacles) {
            auto it = obstacle.blocks.begin();
            while (it!=obstacle.blocks.end())
            {
                if (CheckCollisionRecs(it->GetRect(),alien.GetRect()))
                {
                    it = obstacle.blocks.erase(it); // do not need to delete alien
                } else {
                    it ++; // need this line to not be in an endless loop (oops)
                }
            }
        }

        // for every alien, check for collision with the player
        if (CheckCollisionRecs(alien.GetRect(),spaceship.GetRect()))
        {
            // std::cout << "Spaceship hit by alien" << std::endl;
            GameOver();
        }
    }
}

void Game::GameOver()
{
    std::cout << "Game Over" << std::endl;
    run = false;
}

void Game::Reset()
{
    spaceship.Reset();
    aliens.clear();
    alienLasers.clear();
    obstacles.clear();
    mysteryship.alive = false;
}

void Game::InitGame()
{
    score = 0;
    highScore = LoadHighScoreFromFile();
    CheckHighScore();
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    aliensDirection = 1;
    timeLastAlienFired = 0;
    timeLastSpawn = 0;
    mysteryShipSpawnInterval = GetRandomValue(10,20);
    run = true;
    lives = 3;

}

void Game::CheckHighScore()
{
    if (score > highScore)
    {
        highScore = score;
        SaveHighScoreToFile(highScore);
    }
}

void Game::SaveHighScoreToFile(int highScore)
{
    // Save the high score to a text file
    std::ofstream highScoreFile("highscore.txt");
    if (highScoreFile.is_open()) {
        highScoreFile << highScore;
        highScoreFile.close();
    } else {
        std::cerr << "STD::CERR: Failed to save highscore to file." << std::endl;
    }
}

int Game::LoadHighScoreFromFile()
{
    int loadedHighScore = 0;
    std::ifstream highScoreFile("highscore.txt");
    if (highScoreFile.is_open()) {
        highScoreFile >> loadedHighScore;
        highScoreFile.close();
    } else {
        std::cerr << "STD::CERR: Failed to load highscore from file." << std::endl;
    }
    return loadedHighScore;

}
