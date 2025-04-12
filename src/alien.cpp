#include "alien.h"

Texture2D Alien::alienImages[3] = {};

Alien::Alien(int type, Vector2 position)
{
    this -> type = type;
    this -> position = position;

    // Only load in the image if it has not yet been loaded
    // because alienImages is static, it is consistent across all instances of the alien object
    if (alienImages[type-1].id==0)
    {
        switch (type)
        {
            case 1:
                alienImages[0] = LoadTexture("../Graphics/alien_1.png");
                break;
            case 2:
                alienImages[1] = LoadTexture("../Graphics/alien_2.png");
                break;
            case 3:
                alienImages[2] = LoadTexture("../Graphics/alien_3.png");
                break;
            default:
                alienImages[0] = LoadTexture("../Graphics/alien_1.png");
                break;
        }
    }
    // position.x = (GetScreenWidth() - image.width)/2;
    // position.y = (GetScreenHeight() - image.height);
}

void Alien::Update(int direction)
{
    position.x+=direction;
}

void Alien::Draw()
{
    DrawTextureV(alienImages[type-1], position, WHITE);
}

int Alien::GetType()
{
    return type;
}

void Alien::UnloadImages()
{
    for (int i = 0; i<4; i++)
    {
        UnloadTexture(alienImages[i]);
    }
}
