//
// Created by lumom on 24.04.2023.
//

#ifndef RAYLIBSTARTER_RECHTECK_H
#define RAYLIBSTARTER_RECHTECK_H
// alternative zu dem ist #pragma once


struct Rechteck {
    int height;
    int width;
    int pos_x;
    int pos_y;

    int getArea();
    int getPerimeter();
};

#endif //RAYLIBSTARTER_RECHTECK_H
