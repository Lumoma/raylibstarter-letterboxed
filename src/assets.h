#pragma once

#include "includes.h"

class load_Assets
{
public:
    load_Assets(){
        // Menü Textures
        pauseScreenContinue = LoadTexture("assets/graphics/backgrounds/Pause_02.png");
        pauseScreenRestart = LoadTexture("assets/graphics/backgrounds/Pause_03.png");
        pauseScreenQuit = LoadTexture("assets/graphics/backgrounds/Pause_04.png");
        mainMenuStart = LoadTexture("assets/graphics/backgrounds/MainMenu_04.png");
        mainMenuHighscore = LoadTexture("assets/graphics/backgrounds/MainMenu_03.png");
        mainMenuQuit = LoadTexture("assets/graphics/backgrounds/MainMenu_02.png");
    }

    // Menü Textures
    Texture2D pauseScreenContinue;
    Texture2D pauseScreenRestart;
    Texture2D pauseScreenQuit;
    Texture2D mainMenuStart;
    Texture2D mainMenuHighscore;
    Texture2D mainMenuQuit;
};


