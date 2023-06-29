#pragma once

#include "map.h"
#include "gamestate.h"

class game: public map, public gamestate {

public:

    ~game();

    void init();

    void update();

    void draw();



private:
    void initGameStateAndMap();
};
