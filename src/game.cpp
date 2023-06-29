#include "game.h"

void game::init() {

    gamestate::init(); //MainMenu
    map::init(); //Kitchen Map

}

void game::update() {

    gamestate::update();

    if (isGameRunning) {
        map::update();
    }
}

void game::draw() {
    gamestate::draw();

    if (isGameRunning){
        map::draw();
    }
}
