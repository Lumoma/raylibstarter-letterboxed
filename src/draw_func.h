#pragma once

#include "includes.h"

class draw_func {
public:
    draw_func(){
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
    }

    void setDrawMap(Level currentlevel);
    void drawMap();
    void drawCanvasAndMap();
    void unloadMapTextures();

    Texture2D statusBar;

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

private:
    void DrawMapButOnlyOneLayer(const std::string &layername, tson::Map *theMap, Texture &mapTex);
};


