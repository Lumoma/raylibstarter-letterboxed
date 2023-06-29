#include "game.h"

void game::init() {


    //main menu init
    //setGameState(GameState::MainMenu);

    //map init
    setLevelMap(Level::Kitchen);

}

void game::update() {

    //gamestate::update();

    //Pause Screen Implementation
    if (IsKeyPressed(KEY_P))
        gamestate::isPaused = !gamestate::isPaused;

    if(!gamestate::isPaused) {     //pauses the game while being in pause screen

        // Update LevelMap
        switchLevelMap();

        //Fullscreen logic.
        if (IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_ENTER)) {
            if (IsWindowFullscreen()) {
                ToggleFullscreen();
                SetWindowSize(Game::ScreenWidth, Game::ScreenHeight);
            } else {
                SetWindowSize(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
                ToggleFullscreen();
            }
        }

        // Switch for Collision Layer
        if (IsKeyPressed(KEY_SPACE))
           map::keySwitchCol = !map::keySwitchCol;
    }

}



game::~game() {

}

void game::draw() {
    //gamestate::draw();
    map::drawCanvasAndMap();
}
