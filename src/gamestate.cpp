#include "gamestate.h"

void gamestate::init() {

    //main menu init
    setGameState(MainMenu);
    currentMainMenuSelection = M_Start;
}

void gamestate::setGameState(GameState gameState) {

    if(gameState == MainMenu){
        currentGameState = MainMenu;
        currentMainMenuSelection = M_Start;
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

    switch (currentGameState) {

        case MainMenu:

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
        break;

        case GameRunning:
            //Enter Pause Menu
            if (isMainMenu == 0 && isGameRunning == 1 && IsKeyPressed(KEY_P)){
                setGameState(Pause);
            }

            if (IsKeyPressed(KEY_P)) {  //for pausing the game
                setGameState(Pause);
            }

        break;

        case Pause:
            currentPauseMenuSelection = P_Continue;
            currentPauseMenuSelection = static_cast<PauseMenuSelection>(selection(sizeof(PauseMenuSelection)));

            if (IsKeyPressed((KEY_P))) {  //for resuming the game
                    setGameState(GameRunning);
            }
            if (IsKeyPressed(KEY_ENTER)&& currentPauseMenuSelection == P_Continue) {
                    setGameState(GameRunning);  //Starting the Game
            }
            else if (IsKeyPressed(KEY_ENTER)&& currentPauseMenuSelection == P_Restart) {
                    setGameState(Restart);  //Restarting the Game
            }
            else if ((IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_M)) && currentPauseMenuSelection == P_Quit) {
                    setGameState(MainMenu);//Quitting to MainMenu
            }
        break;

        case Restart:
            setGameState(GameRunning);

        break;

        case Quit:
            setGameState(Quit);
            CloseWindow();
        break;
    }

}

void gamestate::draw() {

    if(currentGameState == MainMenu){
        if (currentMainMenuSelection == M_Start)
            DrawTexture(mainMenuStart, 0, 0, WHITE);
        else if (currentMainMenuSelection == M_Highscore)
            DrawTexture(mainMenuHighscore, 0, 0, WHITE);
        else if (currentMainMenuSelection == M_Quit)
            DrawTexture(mainMenuQuit, 0, 0, WHITE);
    }

    else if(currentGameState == Pause){
        if(currentPauseMenuSelection == P_Continue)
            DrawTexture(pauseScreenContinue, 0, 0, WHITE);
        else if(currentPauseMenuSelection == P_Restart)
            DrawTexture(pauseScreenRestart, 0, 0, WHITE);
        else if(currentPauseMenuSelection == P_Quit)
            DrawTexture(pauseScreenQuit, 0, 0, WHITE);
    }
}

int gamestate::selection(int maxOptions) {
    if (IsKeyPressed(KEY_W))
        selectedButton--;
    if (IsKeyPressed(KEY_S))
        selectedButton++;
    if (selectedButton < 0)
        selectedButton = maxOptions - 2;
    if (selectedButton == maxOptions - 1)
        selectedButton = 0;
    return selectedButton;
}
