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

void Cell::countHitValue() {
    if (matchOneRefVal == 0 && matchZeroRefval == 0) {
        hitValue = 0;
    } else if (matchOneRefVal == 0 && matchZeroRefval != 0) {
        hitValue = matchZeroRefval;
    } else if (matchOneRefVal == 1 && matchZeroRefval == 0) {
        hitValue = 100;
    }
}





