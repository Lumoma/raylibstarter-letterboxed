#pragma once

#include "includes.h"

class map {
public:
    map() {
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

        // Torch Animation
        torchBurningSpitesheet = LoadTexture("assets/torch.png");
        torchLitSpitesheet = LoadTexture("assets/torch_lit.png");
    }

    ~map() {
        UnloadTexture(statusBar);
        UnloadTexture(kitchenTileset);
        UnloadTexture(bedroomTileset);
        UnloadTexture(libraryTileset);
        UnloadRenderTexture(canvas);
        UnloadTexture(torchBurningSpitesheet);
        UnloadTexture(torchLitSpitesheet);
    }

    void init();

    void update();

    void draw();

    enum Level {
        Kitchen,
        Bedroom,
        Library
    };

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

    //Torch Animation
    //PLayer Over Torch
    struct Torch {
        int id;
        Vector2 position;
    };

    std::vector<Torch> torches;

    Texture2D torchBurningSpitesheet;
    Texture2D torchLitSpitesheet;

    int framesCounter;
    int framesSpeed;
    int currentTorchFrame;
    int currentLitFrame;
    void drawTorchAnimation(Vector2 playerPos, bool isPlayerOverTorch, bool isEnterKeyPressed);

private:
    void DrawLayerFromMap(const std::string &layername, tson::Map *theMap, Texture &mapTex);

    void setLevelMap(Level currentLevel);




};



