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
    bool run;
    int lives;
    int score;
    int highScore;
    Music music;

private:
    void DeleteInactiveLasers();
    std::vector<Obstacle> CreateObstacles();
    std::vector<Alien> CreateAliens();
    void MoveAliens();
    void MoveDownAliens(int distance);
    void AlienShootLaser();
    void CheckForCollisions(); // function to check all collidable objects in the game
    void GameOver();
    void Reset();
    void InitGame();
    void CheckHighScore();
    void SaveHighScoreToFile(int highScore);
    int  LoadHighScoreFromFile();
    
    int aliensDirection;
    std::vector<Alien> aliens;
    std::vector<Laser> alienLasers;
    float timeLastAlienFired;
    MysteryShip mysteryship;
    Spaceship spaceship;
    std::vector<Obstacle> obstacles;
    constexpr static float alienLaserShootInterval = 0.35; // this constant expression will be initialized at compile time and cannot change
    Sound explosionSound;

    // properties for controlling spawn of mystery ship
    float mysteryShipSpawnInterval;
    float timeLastSpawn;
};