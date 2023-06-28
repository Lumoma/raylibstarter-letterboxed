#include "draw_func.h"

void draw_func::setDrawMap(Level currentlevel) {
    switch (currentlevel) {
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

void draw_func::drawMap() {
    DrawTexture(statusBar, 0, 0, WHITE); // draw status bar
    DrawMapButOnlyOneLayer("Layer 1", theMap.get(), mapTileset); // draw Layer 1
    DrawMapButOnlyOneLayer("Layer 2", theMap.get(), mapTileset); // draw Layer 2
    //DrawMapButOnlyOneLayer("Layer 3", theMap.get(), mapTileset); // draw Layer 3
    DrawMapButOnlyOneLayer("Torch", theMap.get(), mapTileset); // draw Layer Torch
    //DrawMapButOnlyOneLayer("Items", theMap.get(), mapTileset); // draw Layer Light
    if (keySwitchCol == 1){
        DrawMapButOnlyOneLayer("Collision", theMap.get(),mapTileset); // draw Collision Layer
    }
}

void draw_func::unloadMapTextures() {
    UnloadTexture(kitchenTileset);
    UnloadTexture(bedroomTileset);
    UnloadTexture(libraryTileset);
    UnloadTexture(statusBar);
    UnloadRenderTexture(canvas);
}

void draw_func::DrawMapButOnlyOneLayer(const std::string &layername, tson::Map *theMap, Texture &mapTex) {
    Rectangle sourceRec {0,0,TILE_SIZE,TILE_SIZE};
    Vector2 destVec{};
    const float yOffset = 2 * TILE_SIZE; //offset for the status bar
    int tilesetColumns = 10;
    for (int y = 0; y < TILE_MAP_ROWS; y++) {
        for (int x = 0; x < TILE_MAP_COLUMNS; x++) {
            int tileData = theMap->getLayer(layername)->getData()[x + y * TILE_MAP_COLUMNS] -
                           1; //-1 because tiled does stuff >:(
            if (tileData < 0) continue;
            sourceRec.x = (tileData % tilesetColumns) * TILE_SIZE;
            sourceRec.y = (tileData / tilesetColumns) * TILE_SIZE;
            destVec.x = x * TILE_SIZE;
            destVec.y = Y_OFFSET_STATUSBAR + y * TILE_SIZE;
            DrawTextureRec(mapTex, sourceRec, destVec, WHITE);
        }
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
