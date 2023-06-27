#pragma once

#include "includes.h"

class draw_func {
public:
    draw_func(){

        // Kitchen
        kitchenTileset = LoadTexture("assets/graphics/Levelmaps/Level 1/Kitchen_Picture2.png");

        // Bedroom
        bedroomTileset = LoadTexture("assets/graphics/Levelmaps/Level 2/Bedroom_Picture.png");

        // Library
        libraryTileset = LoadTexture("assets/graphics/Levelmaps/Level 3/Library_Picture.png");

        mapPathKitchen = std::filesystem::path("assets/graphics/Levelmaps/Level 1/Kitchen_Map.json");
        mapPathBedroom = std::filesystem::path("assets/graphics/Levelmaps/Level 2/Bedroom_Map.json");
        mapPathLibrary = std::filesystem::path("assets/graphics/Levelmaps/Level 3/Library_Map.json");
    }
    // Kitchen
    Texture2D kitchenTileset;

    // Bedroom
    Texture2D bedroomTileset;

    // Library
    Texture2D libraryTileset;

    tson::Tileson t;
    std::filesystem::path path;
    Texture2D mapTileset;

    //Switch for Collision Layer
    bool keySwitchCol = false;


    std::filesystem::path mapPathKitchen;
    std::filesystem::path mapPathBedroom;
    std::filesystem::path mapPathLibrary;

    std::unique_ptr<tson::Map> theMap;

    void setDrawMap(Level currentlevel);

    void drawMap();

    void DrawMapButOnlyOneLayer(const std::string &layername, tson::Map *theMap, Texture &mapTex);

};


