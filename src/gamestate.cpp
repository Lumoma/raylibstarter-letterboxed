#include "gamestate.h"

void gamestate::init() {

    //main menu init
    setGameState(MainMenu)
    MainMenuSelection = M_Start ;

    //pause menu init
    isPaused = false;
    selectedButton = 0;
    restart = false;

}

void gamestate::setGameState(GameState gameState) {

    if (IsKeyPressed(KEY_P)){
        isPause != isPause;
    }
    else if (isPause == true){
        gameState = Pause;
    }
    else if(isPause == false){
        gameState = GameRunning;
    }
    else if (IsKeyPressed)

    else if (IsKeyPressed(KEY_R)){
        gameState = Restart;
    }

    else if (IsKeyPressed(KEY_Q)){
        gameState = Quit;
    }

    else if (IsKeyPressed(KEY_M)){
        gameState = MainMenu;
    }


}

void gamestate::update() {

    //Pause Screen Implementation
    if (IsKeyPressed(KEY_P))
        gamestate::isPaused = !gamestate::isPaused;

    if(!gamestate::isPaused) {     //pauses the game while being in pause screen

        gameState = GameRunning;

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

    }

    switch (gameState) {

        case MainMenu:

            gamestate::setMainMenuSelection(gamestate::MainMenuSelection);

            DrawTexture(mainMenuStart, 0, 0, WHITE);
            if (mainMenuSelectedButton == 0) {
                DrawTexture(mainMenuStart, 0, 0, WHITE);
            }
            if (selectedButton == 1) {
                DrawTexture(mainMenuHighscore, 0, 0, WHITE);
            }
            if (selectedButton == 2) {
                DrawTexture(mainMenuQuit, 0, 0, WHITE);
            }

            if (IsKeyPressed(KEY_ENTER)) {
                if (selectedButton == 0) {
                    gameState = GameRunning;        //Starting the Game
                } else if (selectedButton == 1) {
                    gameState = GameRunning;        //Highscore Window opens, for now it just starts the game
                } else if (selectedButton == 2) {
                    gameState = Quit;               //EXIT button
                }
            }
            break;

        case GameRunning:
            drawCanvasAndMap();

            if(IsKeyPressed(KEY_M)){    //for going back into main menu while playing
                gameState = MainMenu;
            }

            if (IsKeyPressed(KEY_P)) {  //for pausing the game
                gameState = Pause;
            }
            break;

        case Pause:
            DrawTexture(pauseScreenContinue, 0, 0, WHITE);
            if (selectedButton == 0) {
                DrawTexture(pauseScreenContinue, 0, 0, WHITE);
            }
            if (selectedButton == 1) {
                DrawTexture(pauseScreenRestart, 0, 0, WHITE);
            }
            if (selectedButton == 2) {
                DrawTexture(pauseScreenQuit, 0, 0, WHITE);
            }


            if (IsKeyPressed(KEY_ENTER)) {
                if (selectedButton == 0) {
                    isPaused = false;       //CONTINUE button
                } else if (selectedButton == 1) {
                    restart = true;    //RESTART button: NOTHING HAPPENS YET, we need to include code for RESTART
                } else if (selectedButton == 2) {
                    CloseWindow();                //EXIT button
                }
            }
            break;

        case Restart: //doesnt work yet
            gameState = GameRunning;
            restart = false;
            break;

        case Quit:
            CloseWindow();
            break;
    }

}

void gamestate::draw() {



}


int gamestate::selection(int maxOptions) {
    int selectedButton = 0;
    if (IsKeyPressed(KEY_W))
        selectedButton--;
    if (IsKeyPressed(KEY_S))
        selectedButton++;
    if (selectedButton < 0)
        selectedButton = maxOptions - 1;
    if (selectedButton >= maxOptions)
        selectedButton = 0;
    return selectedButton;
}
void gamestate::setMainMenuSelection(gamestate::MainMenuSelection mainMenuSelection) {
    switch (gamestate::selection(sizeof(mainMenuSelection)))
    {
        case 0:
            mainMenuSelection = M_Start;
        case 1:
            mainMenuSelection =  M_Highscore;
        case 2:
            mainMenuSelection = M_Quit;
        default:
            mainMenuSelection = M_Start;
            break;
    }
}

void gamestate::setPauseMenuSelection(gamestate::PauseMenuSelection pauseMenuSelection) {
    switch (gamestate::selection(sizeof(pauseMenuSelection))) {
        case 0:
            pauseMenuSelection = P_Continue;
        case 1:
            pauseMenuSelection = P_Restart;
        case 2:
            pauseMenuSelection = P_Quit;
        default:
            pauseMenuSelection = P_Continue;
            break;
    }
}
