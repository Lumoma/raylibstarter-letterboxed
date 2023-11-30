#pragma once

#include "map.h"
#include "gamestate.h"
#include "player.h"

class game : public map, public gamestate, public player {
public:
    void init();

    void update();

    void draw();

    bool isPlayerOnTorch;
    bool isTorchLit;


private:
    void checkPlayerCollision();

    bool checkForCollision(Vector2 CollisionTilePos);

};
