#pragma once
#include "includes.h"

class character {
public:
    int stateAge = -1;
    bool isMoving = false;
    int orientation = 0;

    Vector2 spawnPos{};
    Vector2 currentPos{};
    Vector2 targetPos{};
    int posTileX = 0;
    int posTileY = 0;

    Texture2D tex;
    float speed = 2;
    int keyframeDuration = 4;
    int keyframes = 4;

    void draw();
    void drawPosStats();
};

