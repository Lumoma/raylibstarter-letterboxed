#include "torchAnimation.h"

void torchAnimation::init() {
    framesCounter = 0;
    framesSpeed = 6;
    currentTorchFrame = 0;
}

void torchAnimation::update() {
    framesCounter++;
    if (framesCounter >= (60 / framesSpeed)) {
        framesCounter = 0;
        currentTorchFrame++;
        if (currentTorchFrame > 4)
            currentTorchFrame = 0;
    }
    if(IsKeyPressed(KEY_E)){
        lighttorch = true;
    } else {
        lighttorch = false;
    }
}

void torchAnimation::draw(tson::Map *theMap, bool playerOverTorch) {
    Rectangle frameRecTorch = {0.0f, 0.0f, TILE_SIZE, TILE_SIZE};
    int tilesetColumns = 10;
    bool isBurningAnimationFinished = currentTorchFrame >= 4;

    for (int y = 0; y < TILE_MAP_ROWS; y++) {
        for (int x = 0; x < TILE_MAP_COLUMNS; x++) {
            int tileData = theMap->getLayer("Torch")->getData()[x + y * TILE_MAP_COLUMNS] - 1; // -1 because tiled does stuff >:(
            if (tileData < 0)
                continue;
            frameRecTorch.x = (tileData % tilesetColumns) * TILE_SIZE;
            frameRecTorch.y = (tileData / tilesetColumns) * TILE_SIZE;
            torchAnimationDestVec.x = x * TILE_SIZE;
            torchAnimationDestVec.y = Y_OFFSET_STATUSBAR + y * TILE_SIZE;

            if (playerOverTorch && lighttorch) {
                if (isBurningAnimationFinished) {
                    frameRecTorch.x = (float)currentTorchFrame * 32;
                    DrawTextureRec(torchLitSpitesheet, frameRecTorch, torchAnimationDestVec, WHITE);
                } else {
                    frameRecTorch.x = (float)currentTorchFrame * 32;
                    DrawTextureRec(torchBurningSpitesheet, frameRecTorch, torchAnimationDestVec, WHITE);
                }
            }
        }
    }
}
