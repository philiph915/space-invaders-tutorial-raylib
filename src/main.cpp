#include "raylib.h"
#include "spaceship.hpp"
#include "game.h"


int main() 
{
    const Color grey = {29, 29, 27, 255};
    
    constexpr int screenWidth = 750;
    constexpr int screenHeight = 700;

    
    
    InitWindow(screenWidth, screenHeight, "C++ Space Invaders");
    SetTargetFPS(120);

    // Instantiate the game after InitWindow in order to prevent seg faults!
    Game game;
    
    while (!WindowShouldClose())
    {
        game.HandleInput();
        game.Update();
        BeginDrawing();
        ClearBackground(grey);
        game.Draw();

        // Get FPS value and draw it in a custom color
        int fps = GetFPS();  
        DrawText(TextFormat("FPS: %d", fps), 10, 10, 20, WHITE); 

        EndDrawing();
    }
    
    CloseWindow();
}