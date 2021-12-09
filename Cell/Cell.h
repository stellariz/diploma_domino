//
// Created by ruslan on 05.11.2021.
//

#ifndef DIPLOM_DOMINO_CELL_H
#define DIPLOM_DOMINO_CELL_H

#include <vector>

class Cell {
private:
    int posX = 0;
    int posY = 0;
    int curValue = -1;
    int matchValue = 0;

public:
    Cell() = default;

    Cell(int x, int y);

    int getPosX() const {
        return posX;
    }

    void setPosX(int posX) {
        Cell::posX = posX;
    }

    int getPosY() const {
        return posY;
    }

    void setPosY(int posY) {
        Cell::posY = posY;
    }

    int getMatchValue() const {
        return matchValue;
    }

    void incMatchValue() {
        Cell::matchValue++;
        }

    int getCurValueOnField() const {
        return curValue;
    }

    void setCurValueOnField(int curValueOnField) {
        Cell::curValue = curValueOnField;
    }

    void setMatchValue(int matchValue);

    friend bool operator==(const Cell &lhs, const Cell &rhs);

    friend bool operator!=(const Cell &lhs, const Cell &rhs);
};


#endif //DIPLOM_DOMINO_CELL_H
