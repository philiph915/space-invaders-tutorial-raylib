#pragma once
#include "spaceship.hpp"
#include "obstacle.h"
#include "alien.h"
#include "mysteryship.h"


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
    void CheckForCollisions(); // function to check all collidable objects in the game
    int aliensDirection;
    std::vector<Laser> alienLasers;
    constexpr static float alienLaserShootInterval = 0.35; // this constant expression will be initialized at compile time and cannot change
    float timeLastAlienFired;
    MysteryShip mysteryship;

    // properties for controlling spawn of mystery ship
    float mysteryShipSpawnInterval;
    float timeLastSpawn;
    bool run;
};