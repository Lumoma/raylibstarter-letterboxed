#include "game.h"

void game::init() {

    gamestate::init(); //MainMenu

    map::init(); //Kitchen Map

}

void game::update() {

    gamestate::update();

    map::update();

}



game::~game() {

}

void game::draw() {
    //gamestate::draw();
    map::draw();
}
