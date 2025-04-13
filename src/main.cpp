#include "raylib.h"
#include "spaceship.hpp"
#include "game.h"


int main() 
{
    // Create the game window
    int offset = 50;
    constexpr int screenWidth = 750;
    constexpr int screenHeight = 700;
    InitWindow(screenWidth + offset, screenHeight + 2*offset, "C++ Space Invaders");
    SetTargetFPS(120);
    
    // Define UI Parameters
    const Color grey = {29, 29, 27, 255};
    const Color yellow = {243, 216, 63, 255};
    Font font_ui = LoadFontEx("../Font/monogram.ttf", 64, 0, 0);
    Texture2D spaceshipImage = LoadTexture("../Graphics/spaceship.png");

    // Instantiate the game after InitWindow in order to prevent seg faults!
    Game game;
    
    // Run the game loop
    while (!WindowShouldClose())
    {
        game.Update();
        BeginDrawing();
        
        // Draw UI elements
        ClearBackground(grey);  //background color

        DrawRectangleRoundedLinesEx({10,10,780,780}, 0.18f, 20, 2, yellow); // draw borders
        DrawLineEx({25,730}, {775, 730}, 3, yellow); // draw line segment separating UI on the bottom
        
        // Get FPS value and draw it in a custom color
        int fps = GetFPS();  
        DrawText(TextFormat("FPS: %d", fps), 50, 50, 20, WHITE); 
        
        // Draw LEVEL 01 or GAME OVER depending on game state
        if (game.run) {
            DrawTextEx(font_ui, "LEVEL 01",{570,740}, 34, 2, yellow);
        } else {
            DrawTextEx(font_ui, "GAME OVER",{570,740}, 34, 2, yellow);
        }

        // Display number of lives the player has
        for (int i = 0; i < game.lives; i++)
        {
            DrawTextureV(spaceshipImage, {50 + 50*float(i), 745}, WHITE);
        }
        
        // Render game graphics
        game.Draw();
        EndDrawing();
    }
    
    CloseWindow();
}