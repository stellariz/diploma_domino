//
// Created by ruslan on 05.11.2021.
//

#include "Cell.h"

bool operator==(const Cell &lhs, const Cell &rhs) {
    return lhs.posX == rhs.posX &&
           lhs.posY == rhs.posY;
}

bool operator!=(const Cell &lhs, const Cell &rhs) {
    return !(lhs == rhs);
}





