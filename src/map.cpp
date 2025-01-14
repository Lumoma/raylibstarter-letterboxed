#include "map.h"

void map::init() {
    setLevelMap(Level::Kitchen);
    framesCounter = 0;
    framesSpeed = 6;
    currentTorchFrame = 0;
}

void map::setLevelMap(Level currentLevel) {
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

void map::update() {

    // Switch for Collision Layer
    if (IsKeyPressed(KEY_SPACE))
        keySwitchCol = !keySwitchCol;

    // Level Map quick change
    if (IsKeyPressed(KEY_ONE)) {
        setLevelMap(Level::Kitchen);
    } else if (IsKeyPressed(KEY_TWO)) {
        setLevelMap(Level::Bedroom);
    } else if (IsKeyPressed(KEY_THREE)) {
        setLevelMap(Level::Library);
    }
}

void map::DrawLayerFromMap(const std::string &layername, tson::Map *theMap, Texture &mapTex) {
    Rectangle sourceRec{0, 0, TILE_SIZE, TILE_SIZE};
    Vector2 destVec{};
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

void map::draw() {
    DrawTexture(statusBar, 0, 0, WHITE); // draw status bar
    DrawLayerFromMap("Layer 1", theMap.get(), mapTileset); // draw Layer 1
    DrawLayerFromMap("Layer 2", theMap.get(), mapTileset); // draw Layer 2
    //DrawLayerFromMap("Layer 3", theMap.get(), mapTileset); // draw Layer 3
    DrawLayerFromMap("Torch", theMap.get(), mapTileset); // draw Layer Torch
    //DrawLayerFromMap("Items", theMap.get(), mapTileset); // draw Layer Items
    if (keySwitchCol == 1) {
        DrawLayerFromMap("Collision", theMap.get(), mapTileset); // draw Collision Layer
    }
}


void map::initTorchPositions() {
    for (int y = 0; y < TILE_MAP_ROWS; y++) {
        for (int x = 0; x < TILE_MAP_COLUMNS; x++) {
            int tileData = theMap->getLayer("Torch")->getData()[x + y * TILE_MAP_COLUMNS] - 1; // -1 because tiled does stuff >:(
            if (tileData < 0)
                continue;

            torch.id = tileData;
            torch.position.x = x * TILE_SIZE;
            torch.position.y = Y_OFFSET_STATUSBAR + y * TILE_SIZE;

            torches.push_back(torch); // Füge die Fackel zum Array hinzu
        }
    }
}

void map::updateTorchAnimation() {
    if (currentTorchFrame >= 4) {
        currentLitFrame++;
        if (currentLitFrame >= 4) {
            currentLitFrame = 0;
        }
    } else {
        currentTorchFrame++;
        if (currentTorchFrame >= 4) {
            currentTorchFrame = 0;
        }
    }
}

void map::drawTorchAnimation(Vector2 playerPos, bool isEKeyPressed) {
    for (const auto& torch : torches) {
        Rectangle frameRecBurning = { (float)currentTorchFrame * 32, (float)(torch.id / 10) * 32, 32, 32 };
        Rectangle frameRecLit = { (float)currentLitFrame * 32, (float)(torch.id / 10) * 32, 32, 32 };

        if (currentTorchFrame >= 4 ) {
            DrawTextureRec(torchLitSpitesheet, frameRecLit, torch.position, WHITE);
        } else {
            DrawTextureRec(torchBurningSpitesheet, frameRecBurning, torch.position, WHITE);
        }
    }
}

