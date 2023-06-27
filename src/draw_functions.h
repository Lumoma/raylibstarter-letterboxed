#pragma once

#include "includes.h"

void DrawMapButOnlyOneLayer(const std::string &layername, tson::Map *theMap, Texture &mapTex) {
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