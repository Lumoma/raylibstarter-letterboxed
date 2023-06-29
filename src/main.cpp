#include "game.h"

int main() {

    /// Raylib initialization
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
    SetTargetFPS(60);

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif
    /// Initialization code ///

    game Game;
    Game.init();

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        Game.update();

        BeginDrawing();
        // You can draw on the screen between BeginDrawing() and EndDrawing()
        // For the letterbox we draw on canvas instead
        Game.draw();

        EndDrawing();
    } // Main game loop end

    // De-initialization here
    Game.~game();


    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}
