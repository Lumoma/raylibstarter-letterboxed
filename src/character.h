#pragma once

#include "includes.h"

class character {
public:
    int stateAge = -1;
    bool isMoving;
    int orientation;

    Vector2 spawnPos;
    Vector2 currentPos;
    Vector2 targetPos;
    Vector2 tilePos;

    Texture2D tex;
    const float animationDuration = 16;
    const float speed = TILE_SIZE / animationDuration;
    const int keyframeDuration = 4;
    const int keyframes = 4;

    void calculateTilePos();

    void draw();

    void drawPosStats();

};

