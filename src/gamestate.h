#pragma once

#include "includes.h"

class gamestate {
public:
    gamestate(){
        // Menü Textures
        pauseScreenContinue = LoadTexture("assets/graphics/backgrounds/Pause_02.png");
        pauseScreenRestart = LoadTexture("assets/graphics/backgrounds/Pause_03.png");
        pauseScreenQuit = LoadTexture("assets/graphics/backgrounds/Pause_04.png");
        mainMenuStart = LoadTexture("assets/graphics/backgrounds/MainMenu_04.png");
        mainMenuHighscore = LoadTexture("assets/graphics/backgrounds/MainMenu_03.png");
        mainMenuQuit = LoadTexture("assets/graphics/backgrounds/MainMenu_02.png");
    }

    ~gamestate(){
        UnloadTexture(pauseScreenContinue);
        UnloadTexture(pauseScreenRestart);
        UnloadTexture(pauseScreenQuit);
        UnloadTexture(mainMenuStart);
        UnloadTexture(mainMenuHighscore);
        UnloadTexture(mainMenuQuit);
    }

    void init();
    void update();
    void draw();

    // Menü Textures
    Texture2D pauseScreenContinue{};
    Texture2D pauseScreenRestart{};
    Texture2D pauseScreenQuit{};
    Texture2D mainMenuStart{};
    Texture2D mainMenuHighscore{};
    Texture2D mainMenuQuit{};

    enum GameState {
        MainMenu,
        GameRunning,
        Pause,
        Restart,
        Quit
    };

    GameState* pGameState;

    void setGameState(GameState gameState);

    enum MainMenuSelection {
        M_Start = 0,
        M_Highscore = 1,
        M_Quit = 2
    };

    void setMainMenuSelection(MainMenuSelection mainMenuSelection);

    enum PauseMenuSelection {
        P_Continue = 0,
        P_Restart = 1,
        P_Quit = 2
    };

    void setPauseMenuSelection(PauseMenuSelection pauseMenuSelection);

    //Menü Variables
    bool isMainMenu;
    bool isGameRunning;
    bool isPause;

private:
    int selection(int maxOptions);
};


