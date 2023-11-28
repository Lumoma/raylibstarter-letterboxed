//
// Created by lumom on 24.04.2023.
//

#include "Rechteck.h"

int Rechteck::getPerimeter() {
    return (2 * height) + (2 * width);
}

int Rechteck::getArea() {
    return height * width;
}