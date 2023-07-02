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

    //Torch Animation
    framesCounter++;
    if (framesCounter >= (60 / framesSpeed)) {
        framesCounter = 0;
        currentTorchFrame++;
        if (currentTorchFrame > 4)
            currentTorchFrame = 0;
    }
    currentLitFrame = currentTorchFrame;

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

void map::drawTorchAnimation(Vector2 playerPos, bool isPlayerOverTorch, bool isEnterKeyPressed) {
    Rectangle frameRecBurning = {0.0f, 0.0f, TILE_SIZE, TILE_SIZE};
    Rectangle frameRecLit = {0.0f, 0.0f, TILE_SIZE, TILE_SIZE};
    Vector2 destVec{};
    int tilesetColumns = 10;
    bool isBurningAnimationFinished = currentTorchFrame >= 4;

    for (int y = 0; y < TILE_MAP_ROWS; y++) {
        for (int x = 0; x < TILE_MAP_COLUMNS; x++) {
            int tileData = theMap->getLayer("Torch")->getData()[x + y * TILE_MAP_COLUMNS] - 1; // -1 because tiled does stuff >:(
            if (tileData < 0)
                continue;

            Torch torch;
            torch.id = tileData;
            torch.position.x = x * TILE_SIZE;
            torch.position.y = Y_OFFSET_STATUSBAR + y * TILE_SIZE;

            torches.push_back(torch); // Füge die Fackel zum Array hinzu
        }
    }

    // Schleife zum Zeichnen der Animationen basierend auf den Positionen im Array
    for (const auto& torch : torches) {
        int torchId = torch.id;
        Vector2 torchPosition = torch.position;

        frameRecBurning.x = (torchId % tilesetColumns) * TILE_SIZE;
        frameRecBurning.y = (torchId / tilesetColumns) * TILE_SIZE;
        frameRecLit.x = frameRecBurning.x;
        frameRecLit.y = frameRecBurning.y;

        // Überprüfe, ob der Spieler über der Fackel steht und die Enter-Taste gedrückt hat
        if (isPlayerOverTorch && isEnterKeyPressed && playerPos.x == torchPosition.x && playerPos.y == torchPosition.y) {
            if (isBurningAnimationFinished) {
                // Zeichne die leuchtende Fackel-Animation
                frameRecLit.x += (float)currentLitFrame * 32;
                DrawTextureRec(torchLitSpitesheet, frameRecLit, torchPosition, WHITE);
            } else {
                // Zeichne die brennende Fackel-Animation
                frameRecBurning.x += (float)currentTorchFrame * 32;
                DrawTextureRec(torchBurningSpitesheet, frameRecBurning, torchPosition, WHITE);
            }
        } else {
            // Zeichne die brennende Fackel-Animation
            frameRecBurning.x += (float)currentTorchFrame * 32;
            DrawTextureRec(torchBurningSpitesheet, frameRecBurning, torchPosition, WHITE);
        }
    }
}
