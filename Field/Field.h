//
// Created by ruslan on 05.11.2021.
//

#ifndef DIPLOM_DOMINO_FIELD_H
#define DIPLOM_DOMINO_FIELD_H

#include <iostream>
#include "FieldConfig.h"
#include "../Cell/Cell.h"


class Field {
private:
    Cell *mainField;
    Cell *procField;

    void attachTemplateA1(Cell &cell);

    void attachTemplateA2(Cell &cell);

    void attachTemplateA3(Cell &cell);

    void attachTemplateA4(Cell &cell);

    void attachTemplateA5(Cell &cell);

    void attachTemplateA6(Cell &cell);

    void attachTemplateA7(Cell &cell);

    void attachTemplateA8(Cell &cell);

    void attachTemplateA9(Cell &cell);

    void attachTemplateA10(Cell &cell);

    void attachTemplateA11(Cell &cell);

    void attachTemplateA12(Cell &cell);

    std::vector<Cell> getBigHorizontalHull(Cell &left, Cell &right);

    std::vector<Cell> getBigVerticalHull(Cell &top, Cell &bottom);

    std::vector<Cell> getSmallHull(Cell &leftTopCorner, Cell &firstKernelCell, Cell &secondKetnelCell);

    static bool checkSmallTemplateBounds(int x, int y);

    static bool checkBigTemplateHorizontalBounds(int x, int y);

    static bool checkBigTemplateVerticalBounds(int x, int y);

    static bool isInBounds(int x, int y);

    static bool validateHull(std::vector<Cell> &hull);

    static bool validateKernel(Cell &left, Cell &right);

    const int PROBABILITY = 50;

public:
    Cell &getCell(int x, int y) {
        return mainField[y * FieldConfig::LENGTH + x];
    }

    void initProcField(int sizeOfData, int shiftVec);

    void applyFirstRule(Cell &cell, int shiftVec);

    Field();

    ~Field();

    void printMainField();

    void printProcField(int sizeOfData);

    Cell* getMainField();

    Cell* getProcField();
};


#endif //DIPLOM_DOMINO_FIELD_H
