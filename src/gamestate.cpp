#include "gamestate.h"

/*void gamestate::init() {
    mainMenuSelectedButton = 0;

    //pause menu init
    isPaused = false;
    selectedButton = 0;
    restart = false;

}

void gamestate::setGameState(GameState gameState) {
    if (IsKeyPressed(KEY_W))
        selectedButton--;
    if (IsKeyPressed(KEY_S))
        selectedButton++;
    if (selectedButton < 0)
        selectedButton = buttonCount - 1;
    if (selectedButton >= buttonCount)
        selectedButton = 0;

}

void gamestate::update() {

    switch (gameState) {

        case MainMenu:
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
*/