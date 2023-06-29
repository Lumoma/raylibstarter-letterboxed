#pragma once

#include "draw_func.h"

class gamestate: public draw_func {
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

    //Menü Variables
    bool isPaused;
    bool restart;
    const int mainMenuButtonCount = 3;
    const int buttonCount = 3;
    int imainMenuSelectedButton;
    int iselectedButton;

    GameState gameState;
    MainMenuSelection mainMenuSelectedButton;
    PauseMenuSelection selectedButton;

    void setGameState(GameState gameState);
};


