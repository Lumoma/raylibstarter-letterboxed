#pragma once

#include "includes.h"

tson::Tileson t;
std::filesystem::path path;
Texture2D mapTileset;

enum class Level {
    Kitchen,
    Bedroom,
    Library
};

enum GameState {
    MainMenu,
    GameRunning,
    Quit
};

//Pause function
bool isPaused = false;

//Switch for Collision Layer
bool keySwitchCol = false;
