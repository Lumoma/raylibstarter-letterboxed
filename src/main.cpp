#include "game.h"

int main() {

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
    SetTargetFPS(60);

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    //Initialization
    game Game;
    Game.init();

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        Game.update();

        BeginDrawing();

        Game.draw();

        EndDrawing();
    } // Main game loop end






    // De-initialization here
    Game.~game();

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}
