#include "game.h"

void game::init() {
    gamestate::init(); //MainMenu
    map::init(); //Kitchen Map
    player::init(); //player

}

void game::update() {
    gamestate::update();
    if (isGameRunning) {
        map::update();
        checkPlayerCollision();
        player::update();
    } else if (isRestart) {
        map::init();
        player::init();
    }
}

void game::draw() {

    BeginTextureMode(canvas);
    { //Within this block is where we draw our app to the canvas.
        ClearBackground(WHITE);
        //Drawing Map
        gamestate::draw();
        if (isGameRunning) {
            map::draw();
            player::draw();
            player::drawPosStats();
        }
    }
    EndTextureMode();
    //The following lines put the canvas in the middle of the window and have the negative as black
    ClearBackground(BLACK);
    renderScale = std::min(GetScreenHeight() /
                           (float) canvas.texture.height, //Calculates how big or small the canvas has to be rendered.
                           GetScreenWidth() / (float) canvas.texture.width);
    renderRec.width = canvas.texture.width * renderScale;
    renderRec.height = canvas.texture.height * renderScale;
    renderRec.x = (GetScreenWidth() - renderRec.width) / 2.0f;
    renderRec.y = (GetScreenHeight() - renderRec.height) / 2.0f;
    DrawTexturePro(canvas.texture, Rectangle{0, 0, (float) canvas.texture.width, (float) -canvas.texture.height},
                   renderRec, {}, 0, WHITE);
}

bool game::checkForCollision(Vector2 CollisionTilePos) {
    int tileData = map::theMap->getLayer("Collision")->getData()[CollisionTilePos.x + CollisionTilePos.y * 30];
    return tileData;
}

void game::checkPlayerCollision() {
    calculateTilePos();
    collisionNorth = checkForCollision({player::tilePos.x, player::tilePos.y - 1});
    collisionSouth = checkForCollision({player::tilePos.x, player::tilePos.y + 1});
    collisionEast = checkForCollision({player::tilePos.x + 1, player::tilePos.y});
    collisionWest = checkForCollision({player::tilePos.x - 1, player::tilePos.y});
}


