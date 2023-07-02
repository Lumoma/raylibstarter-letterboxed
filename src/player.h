#pragma once

#include "character.h"
#include "map.h"

class player : public character {
public:
    player() {
        playerSpritesheet = LoadTexture("assets/graphics/Spritesheets/player_spritesheet_v2.png");
    }

    ~player() {
        UnloadTexture(playerSpritesheet);
    }

    Texture2D playerSpritesheet;

    bool collisionNorth;
    bool collisionSouth;
    bool collisionEast;
    bool collisionWest;

    void init();

    void update();

private:
    void playerMovement();
};