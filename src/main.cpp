#include "includes.h"

int main() {

    // Raylib initialization
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
    SetTargetFPS(60);

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    // Load assets //
    load_Assets loadAssets;

    // Initialization code //
    // Canvas
    RenderTexture2D canvas = LoadRenderTexture(Game::ScreenWidth, Game::ScreenHeight);
    float renderScale{}; //those two are relevant to drawing and code-cleanliness
    Rectangle renderRec{};

    // Map loading
    Level currentLevel = Level::Kitchen; // Anfangslevel
    std::unique_ptr<tson::Map> theMap = t.parse(loadAssets.mapPathKitchen);
    mapTileset = loadAssets.kitchenTileset;

    //...............................................



    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        //Pause Screen Implementation
        if (IsKeyPressed(KEY_P))
            isPaused = !isPaused;

        if(!isPaused) {     //pauses the game while being in pause screen

            // Level Map quick change
            if (IsKeyPressed(KEY_ONE)) {
                currentLevel = Level::Kitchen;
                mapTileset = loadAssets.kitchenTileset;
                theMap = t.parse(loadAssets.mapPathKitchen);
            } else if (IsKeyPressed(KEY_TWO)) {
                currentLevel = Level::Bedroom;
                mapTileset = loadAssets.bedroomTileset;
                theMap = t.parse(loadAssets.mapPathBedroom);
            } else if (IsKeyPressed(KEY_THREE)) {
                currentLevel = Level::Library;
                mapTileset = loadAssets.libraryTileset;
                theMap = t.parse(loadAssets.mapPathLibrary);
            }

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
                keySwitchCol = !keySwitchCol;
        }

        BeginDrawing();
        // You can draw on the screen between BeginDrawing() and EndDrawing()
        // For the letterbox we draw on canvas instad
        BeginTextureMode(canvas);
        { //Within this block is where we draw our app to the canvas.
            ClearBackground(WHITE);

            //Drawing Status Bar
            DrawTexture(loadAssets.statusBar, 0, 0, WHITE);

            DrawMapButOnlyOneLayer("Layer 1", theMap.get(), mapTileset); // draw Layer 1
            DrawMapButOnlyOneLayer("Layer 2", theMap.get(), mapTileset); // draw Layer 2
            //DrawMapButOnlyOneLayer("Layer 3", theMap.get(), mapTileset); // draw Layer 3
            DrawMapButOnlyOneLayer("Torch", theMap.get(), mapTileset); // draw Layer Torch
            //DrawMapButOnlyOneLayer("Items", theMap.get(), mapTileset); // draw Layer Light
            if (keySwitchCol == 1)
            {
                DrawMapButOnlyOneLayer("Collision", theMap.get(),mapTileset); // draw Collision Layer
            }

        }
        EndTextureMode();
        //The following lines put the canvas in the middle of the window and have the negative as black
        ClearBackground(BLACK);
        renderScale = std::min(GetScreenHeight() /
                               (float) canvas.texture.height, //Calculates how big or small the canvas has to be rendered.
                               GetScreenWidth() / (float) canvas.texture.width);
        renderRec.width = canvas.texture.width * renderScale;
        renderRec.height = canvas.texture.height * renderScale;
        renderRec.x = (GetScreenWidth() - renderRec.width) / 2.0f;
        renderRec.y = (GetScreenHeight() - renderRec.height) / 2.0f;
        DrawTexturePro(canvas.texture, Rectangle{0, 0, (float) canvas.texture.width, (float) -canvas.texture.height},
                       renderRec,
                       {}, 0, WHITE);
        EndDrawing();
    } // Main game loop end

    // De-initialization here
    UnloadTexture(loadAssets.kitchenTileset);
    UnloadTexture(loadAssets.bedroomTileset);
    UnloadTexture(loadAssets.libraryTileset);
    UnloadTexture(loadAssets.statusBar);

    // ...
    // ...

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}
