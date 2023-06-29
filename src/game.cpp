#include "game.h"

void game::init() {

    gamestate::init(); //MainMenu
    map::init(); //Kitchen Map

}

void game::update() {

    //Fullscreen logic.
    if (IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_F)) {
        if (IsWindowFullscreen()) {
            ToggleFullscreen();
            SetWindowSize(Game::ScreenWidth, Game::ScreenHeight);
        } else {
            SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
            ToggleFullscreen();
        }
    }

    gamestate::update();

    if (isGameRunning) {
        map::update();
    }
    else if (isRestart) {
       map::init();
    }
}

void game::draw() {
    gamestate::draw();

    if (isGameRunning){
        map::draw();
    }
}


