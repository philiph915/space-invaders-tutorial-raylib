#include "raylib.h"
#include "spaceship.hpp"

int main() 
{
    const Color grey = {29, 29, 27, 255};
    
    constexpr int screenWidth = 750;
    constexpr int screenHeight = 700;

    
    
    InitWindow(screenWidth, screenHeight, "C++ Space Invaders");
    SetTargetFPS(60);

    // Instantiate objects after InitWindow
    Spaceship player;
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(grey);
        player.Draw();

        // Get FPS value and draw it in a custom color
        int fps = GetFPS();  
        DrawText(TextFormat("FPS: %d", fps), 10, 10, 20, WHITE); 

        EndDrawing();
    }
    
    CloseWindow();
}