#pragma once
#include "raylib.h"

class Alien 
{
public:
    Alien(int type, Vector2 position);
    void Update(int direction);
    void Draw();
    int GetType();
    // Texture2D image;
    static Texture2D alienImages[3]; // static property; shared across all instances of the class
    static void UnloadImages();
    int type;
    Vector2 position;
private:

};