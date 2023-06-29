#pragma once

#include "raylib.h"
#include "tileson.hpp"
#include "config.h"
#include "defines.h"

/* Draw Class */

class draw_func {
public:

    enum Level {
        Kitchen,
        Bedroom,
        Library
    };

};

/*! \class draw_func
 *  \brief Class for drawing.
 *
 *  This class is used for drawing the map, the canvas an the status bar.
 *  It also loads and unloads the textures.
 *  It also has a switch for showing the collision layer with hotkeys.
 *
 */


