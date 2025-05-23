#include "laser.h"

Laser::Laser(Vector2 position, int speed)
{
    this -> position = position; // use the -> operator when "this" is a pointer (it always is in C++) 
    this -> speed = speed;  // the -> is a shortcut to get the attributes of an object through a pointer (very powerful!)
    active = true;
}

void Laser::Update()
{
    position.y+=speed;
    if (active)
    {
        if (position.y > GetScreenHeight() - 100 || position.y < 25)
        {
            active = false;
        }
    }
}

void Laser::Draw()
{
    if (active)
    {
        DrawRectangle(position.x, position.y, 4, 15, {243, 216, 63, 255} );
    }
}

Rectangle Laser::GetRect()
{
    return Rectangle{position.x,position.y,4,15};
}
