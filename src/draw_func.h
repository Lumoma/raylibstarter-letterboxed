#pragma once

#include "includes.h"

/* Draw Class */

class draw_func {
public:
    draw_func(){
        // Menü Textures
        pauseScreenContinue = LoadTexture("assets/graphics/backgrounds/Pause_02.png");
        pauseScreenRestart = LoadTexture("assets/graphics/backgrounds/Pause_03.png");
        pauseScreenQuit = LoadTexture("assets/graphics/backgrounds/Pause_04.png");
        mainMenuStart = LoadTexture("assets/graphics/backgrounds/MainMenu_04.png");
        mainMenuHighscore = LoadTexture("assets/graphics/backgrounds/MainMenu_03.png");
        mainMenuQuit = LoadTexture("assets/graphics/backgrounds/MainMenu_02.png");

        // Statusbar
        statusBar = LoadTexture("assets/graphics/backgrounds/stats_bar.png");

        // Kitchen
        kitchenTileset = LoadTexture("assets/graphics/Levelmaps/Level 1/Kitchen_Picture2.png");
        mapPathKitchen = std::filesystem::path("assets/graphics/Levelmaps/Level 1/Kitchen_Map.json");

        // Bedroom
        bedroomTileset = LoadTexture("assets/graphics/Levelmaps/Level 2/Bedroom_Picture.png");
        mapPathBedroom = std::filesystem::path("assets/graphics/Levelmaps/Level 2/Bedroom_Map.json");

        // Library
        libraryTileset = LoadTexture("assets/graphics/Levelmaps/Level 3/Library_Picture.png");
        mapPathLibrary = std::filesystem::path("assets/graphics/Levelmaps/Level 3/Library_Map.json");

        // Canvas
        canvas = LoadRenderTexture(Game::ScreenWidth, Game::ScreenHeight);
    }

    ~draw_func(){
        UnloadTexture(pauseScreenContinue);
        UnloadTexture(pauseScreenRestart);
        UnloadTexture(pauseScreenQuit);
        UnloadTexture(mainMenuStart);
        UnloadTexture(mainMenuHighscore);
        UnloadTexture(mainMenuQuit);
        UnloadTexture(statusBar);
        UnloadTexture(kitchenTileset);
        UnloadTexture(bedroomTileset);
        UnloadTexture(libraryTileset);
        UnloadRenderTexture(canvas);
        UnloadTexture(mapTileset);
    }
    enum Level {
        Kitchen,
        Bedroom,
        Library
    };

    enum GameState {
        MainMenu,
        GameRunning,
        Pause,
        Restart,
        Quit
    };

    enum MainMenuSelection {
        M_Start = 0,
        M_Highscore = 1,
        M_Quit = 2
    };
    
    enum PauseMenuSelection {
        P_Continue = 0,
        P_Restart = 1,
        P_Quit = 2
    };

    void initGameStateAndMap();
    void switchLevelMap();
    void setGameState(GameState gameState);
    void drawGameState();

    // Menü Textures
    Texture2D pauseScreenContinue{};
    Texture2D pauseScreenRestart{};
    Texture2D pauseScreenQuit{};
    Texture2D mainMenuStart{};
    Texture2D mainMenuHighscore{};
    Texture2D mainMenuQuit{};

    //Menü Variables

    bool isPaused;
    bool restart;
    const int mainMenuButtonCount = 3;
    const int buttonCount = 3;
    int mainMenuSelectedButton;
    int selectedButton;

    // Statusbar
    Texture2D statusBar;

    // Canvas
    RenderTexture2D canvas;
    float renderScale{};
    Rectangle renderRec{};

    // Kitchen
    Texture2D kitchenTileset;
    std::filesystem::path mapPathKitchen;

    // Bedroom
    Texture2D bedroomTileset;
    std::filesystem::path mapPathBedroom;

    // Library
    Texture2D libraryTileset;
    std::filesystem::path mapPathLibrary;

    //Map Data
    tson::Tileson t;
    std::filesystem::path path;
    Texture2D mapTileset;
    std::unique_ptr<tson::Map> theMap;

    //Switch for Collision Layer
    bool keySwitchCol = false;

    void drawCanvasAndMap();

    void setLevelMap(Level currentLevel);

private:

    void DrawLayerFromMap(const std::string &layername, tson::Map *theMap, Texture &mapTex);
    void drawMap();

};

/*! \class draw_func
 *  \brief Class for drawing.
 *
 *  This class is used for drawing the map, the canvas an the status bar.
 *  It also loads and unloads the textures.
 *  It also has a switch for showing the collision layer with hotkeys.
 *
 */


