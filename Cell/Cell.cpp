//
// Created by ruslan on 05.11.2021.
//

#include "Cell.h"

Cell::Cell(int x, int y) {
    posX = x;
    posY = y;
}

bool operator==(const Cell &lhs, const Cell &rhs) {
    return lhs.getPosX() == rhs.getPosX() &&
           lhs.getPosY() == rhs.getPosY();
}

bool operator!=(const Cell &lhs, const Cell &rhs) {
    return !(lhs == rhs);
}

void Cell::setMatchValue(int matchValue) {
    Cell::matchValue = matchValue;
}




