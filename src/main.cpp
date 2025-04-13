#include "raylib.h"
#include "spaceship.hpp"
#include "game.h"
#include <string>

std::string FormatWithLeadingZeros(int number, int width)
{
    std::string numberText = std::to_string(number);          // Format number as a string
    int leadingZeros = width - numberText.length();           // Add leading zeros
    numberText = std::string(leadingZeros, '0') + numberText; // creates leadingZeros number of copies of the character '0' (2nd argunment must be CHAR)
    return numberText;
}

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

    // Initialize Sounds and Audio
    InitAudioDevice();


    // Instantiate the game after InitWindow in order to prevent seg faults!
    Game game;
    
    // Run the game loop
    while (!WindowShouldClose())
    {
        UpdateMusicStream(game.music);
        game.Update();
        BeginDrawing();
        
        // Draw UI elements
        ClearBackground(grey);  //background color

        DrawRectangleRoundedLinesEx({10,10,780,780}, 0.18f, 20, 2, yellow); // draw borders
        DrawLineEx({25,730}, {775, 730}, 3, yellow); // draw line segment separating UI on the bottom
        
        // Get FPS value and draw it in a custom color
        int fps = GetFPS();  
        DrawText(TextFormat("FPS: %d", fps), 350, 20, 20, WHITE); 
        
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

        // Draw the current score
        DrawTextEx(font_ui, "SCORE", {50, 15}, 34, 2, yellow);
        std::string scoreText = FormatWithLeadingZeros(game.score, 5);
        DrawTextEx(font_ui, scoreText.c_str(), {50, 40}, 34, 2, yellow);

        // Draw the high score
        DrawTextEx(font_ui, "HIGHSCORE", {570, 15}, 34, 2, yellow);
        std::string highScoreText = FormatWithLeadingZeros(game.highScore, 5);
        DrawTextEx(font_ui, highScoreText.c_str(), {642, 40}, 34, 2, yellow);
        
        
        // Render game graphics
        game.Draw();
        EndDrawing();
    }
    
    CloseWindow();
    CloseAudioDevice();
}