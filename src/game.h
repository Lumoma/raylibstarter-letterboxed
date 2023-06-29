#pragma once

#include "map.h"
#include "gamestate.h"

class game: public map, public gamestate {

public:

    void init();

    void update();

    void draw();

};
