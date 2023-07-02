#include "player.h"
#include "map.h"

void player::init() {
    spawnPos = {672, 448 + Y_OFFSET_STATUSBAR};
    targetPos = spawnPos;
    currentPos = targetPos;
    orientation = 0;
    character::tex = playerSpritesheet;
}

void player::update() {
    stateAge++;
    player::playerMovement();
}

void player::playerMovement() {
    switch (isMoving) {
        case 0:
            // Eastward
            if (IsKeyDown(KEY_D)) {
                orientation = 1;
                if (((currentPos.x + TILE_SIZE) < Game::ScreenWidth) && !collisionEast) {
                    targetPos.x = currentPos.x + TILE_SIZE;
                    isMoving = true;
                    stateAge = 0;
                }
            }

                // Westward
            else if (IsKeyDown(KEY_A)) {
                orientation = 3;
                if ((currentPos.x - TILE_SIZE) >= 0 && !collisionWest) {
                    targetPos.x = currentPos.x - TILE_SIZE;
                    isMoving = true;
                    stateAge = 0;
                }
            }

                // Northward
            else if (IsKeyDown(KEY_W)) {
                orientation = 2;
                if ((currentPos.y - TILE_SIZE) >= Y_OFFSET_STATUSBAR && !collisionNorth) {
                    targetPos.y = currentPos.y - TILE_SIZE;
                    isMoving = true;
                    stateAge = 0;
                }
            }

                // Southward
            else if (IsKeyDown(KEY_S)) {
                orientation = 0;
                if (((currentPos.y + TILE_SIZE) < Game::ScreenHeight) && !collisionSouth) {
                    targetPos.y = currentPos.y + TILE_SIZE;
                    isMoving = true;
                    stateAge = 0;
                }
            }
            break;

        case 1:
            if (Vector2Distance(currentPos, targetPos) <= (speed)) {
                currentPos = targetPos;
            }
            if (currentPos.x < targetPos.x) {
                currentPos.x += speed;
            }
            if (currentPos.x > targetPos.x) {
                currentPos.x -= speed;
            }
            if (currentPos.y < targetPos.y) {
                currentPos.y += speed;
            }
            if (currentPos.y > targetPos.y) {
                currentPos.y -= speed;
            }
            if (currentPos.x == targetPos.x && currentPos.y == targetPos.y) {
                isMoving = false;
            }
            break;
    }
}


