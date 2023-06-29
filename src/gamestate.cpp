#include "gamestate.h"

void gamestate::init() {

    //main menu init
    setGameState(MainMenu);
    currentMainMenuSelection = M_Start;
}

void gamestate::setGameState(GameState gameState) {

    if(gameState == MainMenu){
        currentGameState = MainMenu;
        isMainMenu = true;
        isGameRunning = false;
        isPause = false;
        isRestart = false;
        isQuit = false;
    }

    else if(gameState == GameRunning){
        currentGameState = GameRunning;
        isMainMenu = false;
        isGameRunning = true;
        isPause = false;
        isRestart = false;
        isQuit = false;
    }

    else if(gameState == Pause){
        currentGameState = Pause;
        isMainMenu = false;
        isGameRunning = false;
        isPause = true;
        isRestart = false;
        isQuit = false;
    }

    else if(gameState == Restart){
        currentGameState = Restart;
        isMainMenu = false;
        isGameRunning = false;
        isPause = false;
        isRestart = true;
        isQuit = false;
    }

    else if(gameState == Quit){
        currentGameState = Quit;
        isMainMenu = false;
        isGameRunning = false;
        isPause = false;
        isRestart = false;
        isQuit = true;
    }
}

void gamestate::update() {

    switch (currentGameState) {

        case MainMenu:
            currentMainMenuSelection = M_Start;
            currentMainMenuSelection = static_cast<MainMenuSelection>(selection(sizeof(MainMenuSelection)));
            if (IsKeyPressed(KEY_ENTER)){

                if (currentMainMenuSelection == M_Start){
                    setGameState(GameRunning);
                }
                else if (currentMainMenuSelection == M_Highscore){
                    setGameState(GameRunning);
                }
                else if (currentMainMenuSelection == M_Quit){
                    setGameState(Quit);
                }
            }
            isMainMenu = true;
            isGameRunning = false;
            isPause = false;
            isRestart = false;
            isQuit = false;
        break;

        case GameRunning:
            //Enter Pause Menu
            if (isMainMenu == 0 && isGameRunning == 1 && IsKeyPressed(KEY_P)){
                isPause = true;
                isGameRunning = false;
                isMainMenu = false;
                currentGameState = Pause;
            }

            if (IsKeyPressed(KEY_P)) {  //for pausing the game
                currentGameState = Pause;
            }
            isMainMenu = false;
            isGameRunning = true;
            isPause = false;
            isRestart = false;
            isQuit = false;
        break;

        case Pause:
            currentPauseMenuSelection = P_Continue;
            currentPauseMenuSelection = static_cast<PauseMenuSelection>(selection(sizeof(PauseMenuSelection)));

            //Enter Main Menu
            if (isPause == 1 && isGameRunning == 0 && IsKeyPressed(KEY_M)){
                isMainMenu = true;
                currentGameState = MainMenu;
            }

            if (IsKeyPressed((KEY_P))) {  //for resuming the game
                currentGameState = GameRunning;
            }

            if (IsKeyPressed(KEY_ENTER)) {
                if (currentPauseMenuSelection == P_Continue) {
                    setGameState(GameRunning);  //Starting the Game
                } else if (currentPauseMenuSelection == P_Restart) {
                    setGameState(Restart);  //RESTART button: NOTHING HAPPENS YET, we need to include code for RESTART
                } else if (currentPauseMenuSelection == P_Quit) {
                    setGameState(MainMenu);               //EXIT button
                }
            }
            isMainMenu = false;
            isGameRunning = false;
            isPause = true;
            isRestart = false;
            isQuit = false;
        break;

        case Restart:
            setGameState(GameRunning);
            isMainMenu = false;
            isGameRunning = false;
            isPause = false;
            isRestart = true;
            isQuit = false;

        break;

        case Quit:
            CloseWindow();
            isMainMenu = false;
            isGameRunning = false;
            isPause = false;
            isRestart = false;
            isQuit = true;
        break;
    }

}

void gamestate::draw() {

    if (currentMainMenuSelection == M_Start)
        DrawTexture(mainMenuStart, 0, 0, WHITE);
    else if (currentMainMenuSelection == M_Highscore)
        DrawTexture(mainMenuHighscore, 0, 0, WHITE);
    else if (currentMainMenuSelection == M_Quit)
        DrawTexture(mainMenuQuit, 0, 0, WHITE);

    if(currentPauseMenuSelection == P_Continue)
        DrawTexture(pauseScreenContinue, 0, 0, WHITE);
    else if(currentPauseMenuSelection == P_Restart)
        DrawTexture(pauseScreenRestart, 0, 0, WHITE);
    else if(currentPauseMenuSelection == P_Quit)
        DrawTexture(pauseScreenQuit, 0, 0, WHITE);

}


int gamestate::selection(int maxOptions) {
    if (IsKeyPressed(KEY_W))
        selectedButton--;
    if (IsKeyPressed(KEY_S))
        selectedButton++;
    if (selectedButton < 0)
        selectedButton = maxOptions - 2;
    if (selectedButton == maxOptions)
        selectedButton = 0;
    return selectedButton;
}
