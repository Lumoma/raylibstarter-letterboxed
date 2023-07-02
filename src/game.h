#pragma once

#include "map.h"
#include "gamestate.h"
#include "player.h"

class game: public map, public gamestate, public player {

public:

    void init();

    void update();

    void draw();

private:
    
    bool checkForCollision(int x, int y);
};
