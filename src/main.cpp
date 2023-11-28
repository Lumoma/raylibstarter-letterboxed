#include <cstdlib>
#include <algorithm>

#include "raylib.h"

#include "config.h"
#include <string>

#include "Rechteck.h"



int main() {
    Rechteck r1;

    Rechteck* r_ptr = new Rechteck();

    r1.height= 100;
    r1.width= 200;
    r1.pos_x=500;
    r1.pos_y=200;

    float height = 300.0;
    float width = 300.0;
    int pos_x = GetRandomValue( 0, 960);
    int pos_y = GetRandomValue(0, 540);


    // Raylib initialization
    // Project name, screen size, fullscreen mode etc. can be specified in the config.h.in file
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(Game::ScreenWidth, Game::ScreenHeight, Game::PROJECT_NAME);
    SetTargetFPS(60);

#ifdef GAME_START_FULLSCREEN
    ToggleFullscreen();
#endif

    // Your own initialization code here
    // ...
    // ...
    Texture2D myTexture = LoadTexture("assets/graphics/testimage.png");
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

        if(IsKeyDown(KEY_LEFT)) {
            if(width >0)
            width--;
        }


        if(IsKeyDown(KEY_RIGHT)) {
            if((pos_x + width) < Game::ScreenWidth){
                width++;
            }
        }

        if (IsKeyDown(KEY_UP)) {
            if(width > 0)
            height--;
        }

        if(IsKeyDown(KEY_DOWN)){
            if((pos_y + height) < Game::ScreenHeight){
            height++;
            }
        }

        if(IsKeyDown(KEY_W)) {      //die nächsten 4 Befehle verändern die position des Vierecks
            if((pos_y + height) < Game::ScreenHeight) {
                pos_y--;
            }
        }
        if(IsKeyDown(KEY_S)) {
            if((pos_y + height) < Game::ScreenHeight) {
                pos_y++;
            }
        }
        if(IsKeyDown(KEY_D)){
            if((pos_x + width) < Game::ScreenWidth){
                pos_x++;
            }
        }

        if(IsKeyDown(KEY_A)) {
            pos_x--;
    }
        // Updates that are made by frame are coded here

        // ...

        BeginDrawing();
        // You can draw on the screen between BeginDrawing() and EndDrawing()
        // For the letterbox we draw on canvas instead
        BeginTextureMode(canvas);
        { //Within this block is where we draw our app to the canvas.
            ClearBackground(WHITE);
            DrawText(TextFormat("Area %.2f" , r1.getArea()), 10, 10, 30, LIGHTGRAY);
            DrawText(TextFormat("Circumference %.2f" , r1.getPerimeter()), 10, 50, 30, LIGHTGRAY);

            DrawRectangle(pos_x, pos_y, (int) width, (int) height, PURPLE);
            DrawText(TextFormat("Width %.2f" , width), 700, 10, 30, LIGHTGRAY);
            DrawText(TextFormat("Height %.2f" , height), 700, 50, 30, LIGHTGRAY);
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
    UnloadTexture(myTexture);

    // Close window and OpenGL context
    CloseWindow();

    return EXIT_SUCCESS;
}


