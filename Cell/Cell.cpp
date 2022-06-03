//
// Created by ruslan on 05.11.2021.
//

#include <tuple>
#include "Cell.h"

bool operator==(const Cell &lhs, const Cell &rhs) {
    return lhs.posX == rhs.posX &&
           lhs.posY == rhs.posY;
}

bool operator!=(const Cell &lhs, const Cell &rhs) {
    return !(lhs == rhs);
}

void Cell::countHitValue() {
    if (matchOneRefVal == 0 && matchZeroRefVal == 0) {
        hitValue = 0;
    } else if (matchOneRefVal == 0 && matchZeroRefVal != 0) {
        hitValue = matchZeroRefVal;
    } else if (matchOneRefVal == 1 && matchZeroRefVal == 0) {
        hitValue = 100;
    }
}

bool operator<(const Cell &lhs, const Cell &rhs) {
    return std::tie (lhs.posY, lhs.posX) < std::tie (rhs.posY, rhs.posX);
}





