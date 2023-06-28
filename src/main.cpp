﻿#include "includes.h"

int main() {

    /// Raylib initialization
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
    SetTargetFPS(60);

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif
    /// Initialization code ///

    // Draw function
    draw_func draw;
    draw.initGameStateAndMap();

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        //Pause Screen Implementation
        if (IsKeyPressed(KEY_P))
            draw.isPaused = !draw.isPaused;

        if(!draw.isPaused) {     //pauses the game while being in pause screen

            // Update LevelMap
            draw.switchLevelMap();

            //Fullscreen logic.
            if (IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_ENTER)) {
                if (IsWindowFullscreen()) {
                    ToggleFullscreen();
                    SetWindowSize(Game::ScreenWidth, Game::ScreenHeight);
                } else {
                    SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
                    ToggleFullscreen();
                }
            }

            // Switch for Collision Layer
            if (IsKeyPressed(KEY_SPACE))
                draw.keySwitchCol = !draw.keySwitchCol;
        }

        BeginDrawing();
        // You can draw on the screen between BeginDrawing() and EndDrawing()
        // For the letterbox we draw on canvas instead
        draw.drawCanvasAndMap();

        EndDrawing();
    } // Main game loop end

    // De-initialization here
    draw.~draw_func();

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}
