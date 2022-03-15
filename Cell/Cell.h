//
// Created by ruslan on 05.11.2021.
//

#ifndef DIPLOM_DOMINO_CELL_H
#define DIPLOM_DOMINO_CELL_H

#include <vector>

class Cell {
public:
    int posX = 0;
    int posY = 0;
    int curValue = -1;
    int matchZeroRefval = 0;
    int matchOneRefVal = 0;
    int hitValue = -1;

    Cell() = default;

    void countHitValue();

    friend bool operator==(const Cell &lhs, const Cell &rhs);

    friend bool operator!=(const Cell &lhs, const Cell &rhs);
};


#endif //DIPLOM_DOMINO_CELL_H
