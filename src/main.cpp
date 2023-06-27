#include <cstdlib>
#include <algorithm>
#include "tileson.hpp"
#include "raylib.h"
#include "config.h"

const int tileSize = 32;

void DrawMapButOnlyOneLayer(const std::string &layername, tson::Map *theMap, Texture &mapTex) {
    Rectangle sourceRec{};
    sourceRec.width = tileSize;
    sourceRec.height = tileSize;
    Vector2 destVec{};
    const float yOffset = 2 * tileSize; //offset for the status bar
    int tilesetColumns = 10;
    int tileMapColumns = theMap->getSize().x;
    int tileMapRows = theMap->getSize().y;
    for (int y = 0; y < tileMapRows; y++) {
        for (int x = 0; x < tileMapColumns; x++) {
            int tileData = theMap->getLayer(layername)->getData()[x + y * tileMapColumns] -
                           1; //-1 because tiled does stuff >:(
            if (tileData < 0) continue;
            sourceRec.x = (tileData % tilesetColumns) * tileSize;
            sourceRec.y = (tileData / tilesetColumns) * tileSize;
            destVec.x = x * tileSize;
            destVec.y = yOffset + y * tileSize;
            DrawTextureRec(mapTex, sourceRec, destVec, WHITE);
        }
    }
}

tson::Tileson t;
std::filesystem::path path;
Texture2D mapTileset;

int main() {
    // Raylib initialization
    // Project name, screen size, fullscreen mode etc. can be specified in the config.h.in file
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
    SetTargetFPS(60);

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    std::filesystem::path mapPathKitchen("assets/graphics/Levelmap/Kitchen_Map.json");
    Texture2D kitchenTileset = LoadTexture("assets/graphics/Levelmap/Kitchen_Picture2.png");

    std::unique_ptr<tson::Map> theMap = t.parse(mapPathKitchen);
    mapTileset = kitchenTileset;

    bool keySwitchCol = false;  //Switch um die Collision anzuschalten

    // Your own initialization code here
    // ...
    // ...

    RenderTexture2D canvas = LoadRenderTexture(Game::ScreenWidth, Game::ScreenHeight);
    float renderScale{}; //those two are relevant to drawing and code-cleanliness
    Rectangle renderRec{};

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        if (IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_ENTER)) { //Fullscreen logic.
            if (IsWindowFullscreen()) {
                ToggleFullscreen();
                SetWindowSize(Game::ScreenWidth,Game::ScreenHeight);
            } else {
                SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
                ToggleFullscreen();
            }
        }
        // Updates that are made by frame are coded here
        // ...
        // ...
        if (IsKeyPressed(KEY_SPACE) && keySwitchCol == 0) {
            keySwitchCol = true;
        } else if (IsKeyPressed(KEY_SPACE) && keySwitchCol == 1) {
            keySwitchCol = false;
        }

        BeginDrawing();
        // You can draw on the screen between BeginDrawing() and EndDrawing()
        // For the letterbox we draw on canvas instad
        BeginTextureMode(canvas);
        { //Within this block is where we draw our app to the canvas.
            ClearBackground(WHITE);
            DrawMapButOnlyOneLayer("Layer 1", theMap.get(), kitchenTileset); // Layer 1 wird gezeichnet
            DrawMapButOnlyOneLayer("Layer 2", theMap.get(), kitchenTileset); // Layer 2 wird gezeichnet
            DrawMapButOnlyOneLayer("Layer 3", theMap.get(), kitchenTileset); // Layer 3 wird gezeichnet
            DrawMapButOnlyOneLayer("Torch", theMap.get(), kitchenTileset); // Layer Torch wird gezeichnet
            DrawMapButOnlyOneLayer("Items", theMap.get(), kitchenTileset); // Layer Light wird gezeichnet
            if (keySwitchCol == 1) {
                DrawMapButOnlyOneLayer("Collision", theMap.get(),
                                       kitchenTileset); // Layer 3 für Collision wird gezeichnet
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
    // ...
    // ...
    UnloadTexture(kitchenTileset);

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}
