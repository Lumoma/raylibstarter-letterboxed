#pragma once

#include "includes.h"

class load_Assets
{
public:
    load_Assets()
    {
        // Kitchen
        mapPathKitchen = std::filesystem::path("assets/graphics/Levelmaps/Level 1/Kitchen_Map.json");
        kitchenTileset = LoadTexture("assets/graphics/Levelmaps/Level 1/Kitchen_Picture2.png");

        // Bedroom
        mapPathBedroom = std::filesystem::path("assets/graphics/Levelmaps/Level 2/Bedroom_Map.json");
        bedroomTileset = LoadTexture("assets/graphics/Levelmaps/Level 2/Bedroom_Picture.png");

        // Library
        mapPathLibrary = std::filesystem::path("assets/graphics/Levelmaps/Level 3/Library_Map.json");
        libraryTileset = LoadTexture("assets/graphics/Levelmaps/Level 3/Library_Picture.png");

        // Background Textures
        statusBar = LoadTexture("assets/graphics/backgrounds/stats_bar.png");
        pauseScreenContinue = LoadTexture("assets/graphics/backgrounds/Pause_02.png");
        pauseScreenRestart = LoadTexture("assets/graphics/backgrounds/Pause_03.png");
        pauseScreenQuit = LoadTexture("assets/graphics/backgrounds/Pause_04.png");
        mainMenuStart = LoadTexture("assets/graphics/backgrounds/MainMenu_04.png");
        mainMenuHighscore = LoadTexture("assets/graphics/backgrounds/MainMenu_03.png");
        mainMenuQuit = LoadTexture("assets/graphics/backgrounds/MainMenu_02.png");
    }

    // Kitchen
    std::filesystem::path mapPathKitchen;
    Texture2D kitchenTileset;

    // Bedroom
    std::filesystem::path mapPathBedroom;
    Texture2D bedroomTileset;

    // Library
    std::filesystem::path mapPathLibrary;
    Texture2D libraryTileset;

    // Background Textures
    Texture2D statusBar;
    Texture2D pauseScreenContinue;
    Texture2D pauseScreenRestart;
    Texture2D pauseScreenQuit;
    Texture2D mainMenuStart;
    Texture2D mainMenuHighscore;
    Texture2D mainMenuQuit;
};


