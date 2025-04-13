#pragma once
#include "raylib.h"
#include "laser.h"
#include <vector>

class Spaceship
{
public:
    Spaceship();
    ~Spaceship();
    void Draw();
    void MoveLeft();
    void MoveRight();
    void FireLaser();
    std::vector<Laser> lasers;
    Rectangle GetRect();
    void Reset();

private:
    Texture2D image;
    Vector2 position;
    double lastFireTime;
    Sound laserSound;

};