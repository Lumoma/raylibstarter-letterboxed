#pragma once
#include "character.h"

class player : public character {
public:
    player() {
        playerSpritesheet = LoadTexture("assets/graphics/Spritesheets/player_spritesheet_v2.png");
    }
    ~player() {
        UnloadTexture(playerSpritesheet);
    }

    Texture2D playerSpritesheet;

    float tileVisibility = 1;

    void init();

    void update();

private:

    void playerMovement();
};
