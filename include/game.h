#pragma once
#include "spaceship.hpp"
#include "obstacle.h"
#include "alien.h"


class Game 
{
public:
    Game();
    ~Game();
    void Draw();
    void Update();
    void HandleInput();

private:
    void DeleteInactiveLasers();
    std::vector<Obstacle> CreateObstacles();
    std::vector<Alien> CreateAliens();
    Spaceship spaceship;
    std::vector<Obstacle> obstacles;
    std::vector<Alien> aliens;
    void MoveAliens();
    void MoveDownAliens(int distance);
    void AlienShootLaser();
    int aliensDirection;
    std::vector<Laser> alienLasers;
};