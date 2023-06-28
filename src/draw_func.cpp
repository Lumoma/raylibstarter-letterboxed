#include "draw_func.h"

void draw_func::DrawLayerFromMap(const std::string &layername, tson::Map *theMap, Texture &mapTex) {
    Rectangle sourceRec {0,0,TILE_SIZE,TILE_SIZE};
    Vector2 destVec{};
    const float yOffset = 2 * TILE_SIZE; //offset for the status bar
    int tilesetColumns = 10;
    for (int y = 0; y < TILE_MAP_ROWS; y++) {
        for (int x = 0; x < TILE_MAP_COLUMNS; x++) {
            int tileData = theMap->getLayer(layername)->getData()[x + y * TILE_MAP_COLUMNS] - 1; //-1 because tiled does stuff >:(
            if (tileData < 0) continue;
            sourceRec.x = (tileData % tilesetColumns) * TILE_SIZE;
            sourceRec.y = (tileData / tilesetColumns) * TILE_SIZE;
            destVec.x = x * TILE_SIZE;
            destVec.y = Y_OFFSET_STATUSBAR + y * TILE_SIZE;
            DrawTextureRec(mapTex, sourceRec, destVec, WHITE);
        }
    }
}

void draw_func::drawMap() {
    DrawTexture(statusBar, 0, 0, WHITE); // draw status bar
    DrawLayerFromMap("Layer 1", theMap.get(), mapTileset); // draw Layer 1
    DrawLayerFromMap("Layer 2", theMap.get(), mapTileset); // draw Layer 2
    //DrawLayerFromMap("Layer 3", theMap.get(), mapTileset); // draw Layer 3
    DrawLayerFromMap("Torch", theMap.get(), mapTileset); // draw Layer Torch
    //DrawLayerFromMap("Items", theMap.get(), mapTileset); // draw Layer Light
    if (keySwitchCol == 1){
        DrawLayerFromMap("Collision", theMap.get(), mapTileset); // draw Collision Layer
    }
}

void draw_func::drawCanvasAndMap() {
    BeginTextureMode(canvas);
    { //Within this block is where we draw our app to the canvas.
        ClearBackground(WHITE);
        //Drawing Map
        draw_func::drawMap();
    }
    EndTextureMode();
    //The following lines put the canvas in the middle of the window and have the negative as black
    ClearBackground(BLACK);
    renderScale = std::min(GetScreenHeight() /(float) canvas.texture.height, //Calculates how big or small the canvas has to be rendered.
                           GetScreenWidth() / (float) canvas.texture.width);
    renderRec.width = canvas.texture.width * renderScale;
    renderRec.height = canvas.texture.height * renderScale;
    renderRec.x = (GetScreenWidth() - renderRec.width) / 2.0f;
    renderRec.y = (GetScreenHeight() - renderRec.height) / 2.0f;
    DrawTexturePro(canvas.texture, Rectangle{0, 0, (float) canvas.texture.width,(float) -canvas.texture.height},
                   renderRec,{}, 0, WHITE);
}

void draw_func::initGameStateAndMap() {

    //main menu init
    setGameState(GameState::MainMenu);
    mainMenuSelectedButton = 0;

    //pause menu init
    isPaused = false;
    selectedButton = 0;
    restart = false;

    //map init
    setLevelMap(Level::Kitchen);
}

void draw_func::setLevelMap(Level currentLevel) {
    switch (currentLevel) {
        case Level::Kitchen:
            path = mapPathKitchen;
            mapTileset = kitchenTileset;
            break;
        case Level::Bedroom:
            path = mapPathBedroom;
            mapTileset = bedroomTileset;
            break;
        case Level::Library:
            path = mapPathLibrary;
            mapTileset = libraryTileset;
            break;
    }
    theMap = t.parse(path);
}

void draw_func::switchLevelMap() {

    // Level Map quick change
    if (IsKeyPressed(KEY_ONE)) {
        setLevelMap(Level::Kitchen);
    } else if (IsKeyPressed(KEY_TWO)) {
        setLevelMap(Level::Bedroom);
    } else if (IsKeyPressed(KEY_THREE)) {
        setLevelMap(Level::Library);
    }
}

void draw_func::setGameState(GameState gameState) {
    if (IsKeyPressed(KEY_W))
        selectedButton--;
    if (IsKeyPressed(KEY_S))
        selectedButton++;
    if (selectedButton < 0)
        selectedButton = buttonCount - 1;
    if (selectedButton >= buttonCount)
        selectedButton = 0;

}

void draw_func::drawGameState() {

    switch (gameState) {

        case MainMenu:
            DrawTexture(mainMenuStart, 0, 0, WHITE);
            if (mainMenuSelectedButton == 0) {
                DrawTexture(mainMenuStart, 0, 0, WHITE);
            }
            if (selectedButton == 1) {
                DrawTexture(mainMenuHighscore, 0, 0, WHITE);
            }
            if (selectedButton == 2) {
                DrawTexture(mainMenuQuit, 0, 0, WHITE);
            }

            if (IsKeyPressed(KEY_ENTER)) {
                if (selectedButton == 0) {
                    gameState = GameRunning;        //Starting the Game
                } else if (selectedButton == 1) {
                    gameState = GameRunning;        //Highscore Window opens, for now it just starts the game
                } else if (selectedButton == 2) {
                    gameState = Quit;               //EXIT button
                }
            }
        break;

        case GameRunning:
            drawCanvasAndMap();

            if(IsKeyPressed(KEY_M)){    //for going back into main menu while playing
                gameState = MainMenu;
            }

            if (IsKeyPressed(KEY_P)) {  //for pausing the game
                gameState = Pause;
            }
        break;

        case Pause:
            DrawTexture(pauseScreenContinue, 0, 0, WHITE);
            if (selectedButton == 0) {
                DrawTexture(pauseScreenContinue, 0, 0, WHITE);
            }
            if (selectedButton == 1) {
                DrawTexture(pauseScreenRestart, 0, 0, WHITE);
            }
            if (selectedButton == 2) {
                DrawTexture(pauseScreenQuit, 0, 0, WHITE);
            }


            if (IsKeyPressed(KEY_ENTER)) {
                if (selectedButton == 0) {
                    isPaused = false;       //CONTINUE button
                } else if (selectedButton == 1) {
                    restart = true;    //RESTART button: NOTHING HAPPENS YET, we need to include code for RESTART
                } else if (selectedButton == 2) {
                    CloseWindow();                //EXIT button
                }
            }
        break;

        case Restart: //doesnt work yet
                gameState = GameRunning;
                restart = false;
        break;

        case Quit:
            CloseWindow();
            break;
    }

}



