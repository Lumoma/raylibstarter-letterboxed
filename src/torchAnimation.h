#pragma once

#include "includes.h"

class torchAnimation {
public:
    torchAnimation(){
        torchBurningSpitesheet = LoadTexture("assets/torch.png");
        torchLitSpitesheet = LoadTexture("assets/torch_lit.png");
    }

    ~torchAnimation(){
        UnloadTexture(torchBurningSpitesheet);
        UnloadTexture(torchLitSpitesheet);
    }

    Texture2D torchBurningSpitesheet;
    Texture2D torchLitSpitesheet;

    int framesCounter;
    int framesSpeed;
    int currentTorchFrame;

    bool lighttorch;
    Vector2 torchAnimationDestVec{};

    void init();

    void update();

    void draw(tson::Map *theMap,bool playerOverTorch);

};

