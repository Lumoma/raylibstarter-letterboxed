#include "character.h"

void character::draw() {
    Rectangle source;
    source.width = TILE_SIZE;
    source.height = TILE_SIZE;
    source.x = isMoving ? (stateAge / keyframeDuration % keyframes) * TILE_SIZE : 0;
    source.y = TILE_SIZE * orientation;
    Rectangle dest;
    dest.width = TILE_SIZE;
    dest.height = TILE_SIZE;
    dest.x = currentPos.x;
    dest.y = currentPos.y;
    DrawTexturePro(tex, source, dest, {}, 0, WHITE);
}

void character::calculateTilePos() {
    tilePos.x = currentPos.x / TILE_SIZE;
    tilePos.y = currentPos.y / TILE_SIZE - (Y_OFFSET_STATUSBAR / TILE_SIZE);
}

void character::drawPosStats() {
    DrawText(TextFormat("player: PosX: %.0f  PosY: %.0f", currentPos.x, currentPos.y - Y_OFFSET_STATUSBAR), 400, 24, 20,WHITE);
    DrawText(TextFormat("Tile PosX: %.0f  Tile PosY: %.0f", tilePos.x, tilePos.y), 24, 24, 20, WHITE);
}


