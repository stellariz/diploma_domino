//
// Created by ruslan on 05.11.2021.
//

#include "Field.h"

Field::Field() {
    field = new Cell[FieldConfig::WIDTH * FieldConfig::LENGTH];
    srand(time(NULL));
    for (int j = 0; j < FieldConfig::WIDTH; ++j) {
        for (int i = 0; i < FieldConfig::LENGTH; ++i) {
            field[j * FieldConfig::LENGTH + i].setCurValueOnField(rand() % 2);
            field[j * FieldConfig::LENGTH + i].setPosX(i);
            field[j * FieldConfig::LENGTH + i].setPosY(j);
        }
    }
}

Field::~Field() {
    delete[] field;
}

void Field::printField() {
    for (int j = 0; j < FieldConfig::WIDTH; ++j) {
        for (int i = 0; i < FieldConfig::LENGTH; ++i) {
            std::cout << "|";
            std::cout << field[j * FieldConfig::LENGTH + i].getCurValueOnField();
        }
        std::cout << "|" << std::endl;
    }
    std::cout << std::endl;
}


bool Field::isInBounds(int x, int y) {
    return x >= 0 && x < FieldConfig::LENGTH &&
           y >= 0 && y < FieldConfig::WIDTH;
}

bool Field::validateKernel(Cell &left, Cell &right) {
    return left.getCurValueOnField() != 0 && right.getCurValueOnField() != 0;
}

bool Field::validateHull(std::vector<Cell> &hull) {
    for (Cell &cell: hull) {
        if (cell.getCurValueOnField() == 1) {
            return false;
        }
    }
    return true;
}


// by left cell
bool Field::checkBigTemplateHorizontalBounds(int x, int y) {
    return isInBounds(x - 1, y + 1) &&
           isInBounds(x - 1, y - 1) &&
           isInBounds(x + 2, y + 1) &&
           isInBounds(x + 2, y - 1);
}

bool Field::checkSmallTemplateBounds(int x, int y) {
    return isInBounds(x - 1, y + 1) &&
           isInBounds(x - 1, y - 1) &&
           isInBounds(x + 1, y + 1) &&
           isInBounds(x + 1, y - 1);
}

// by top cell
bool Field::checkBigTemplateVerticalBounds(int x, int y) {
    return isInBounds(x - 1, y + 1) &&
           isInBounds(x + 1, y + 1) &&
           isInBounds(x - 1, y - 2) &&
           isInBounds(x + 1, y - 2);
}


std::vector<Cell> Field::getSmallHull(Cell &leftTopCorner, Cell &firstKernelCell, Cell &secondKernelCell) {
    std::vector<Cell> area;
    for (int i = leftTopCorner.getPosY(); i <= leftTopCorner.getPosY() + 2; ++i) {
        for (int j = leftTopCorner.getPosX(); j <= leftTopCorner.getPosX() + 2; ++j) {
            if (field[i * FieldConfig::LENGTH + j] != firstKernelCell &&
                field[i * FieldConfig::LENGTH + j] != secondKernelCell) {
                area.push_back(field[i * FieldConfig::LENGTH + j]);
            }
        }
    }
    return area;
}

std::vector<Cell> Field::getBigVerticalHull(Cell &top, Cell &bottom) {
    std::vector<Cell> area;
    for (int i = top.getPosY() - 1; i <= top.getPosY() + 2; ++i) {
        for (int j = top.getPosX() - 1; j <= top.getPosX() + 1; ++j) {
            if (field[i * FieldConfig::LENGTH + j] != top && field[i * FieldConfig::LENGTH + j] != bottom) {
                area.push_back(field[i * FieldConfig::LENGTH + j]);
            }
        }
    }
    return area;
}

std::vector<Cell> Field::getBigHorizontalHull(Cell &left, Cell &right) {
    std::vector<Cell> area;
    for (int i = left.getPosY() - 1; i <= left.getPosY() + 1; ++i) {
        for (int j = left.getPosX() - 1; j <= left.getPosX() + 2; ++j) {
            if (field[i * FieldConfig::LENGTH + j] != left && field[i * FieldConfig::LENGTH + j] != right) {
                area.push_back(field[i * FieldConfig::LENGTH + j]);
            }
        }
    }
    return area;
}

void Field::attachTemplateA1(Cell &cell) {
    if (checkBigTemplateHorizontalBounds(cell.getPosX(), cell.getPosY())) {
        Cell right = getCell(cell.getPosX() + 1, cell.getPosY());
        std::vector<Cell> hull = getBigHorizontalHull(cell, right);
        if (validateHull(hull) && validateKernel(cell, right)) {
            cell.setCurValueOnField(1);
            cell.incMatchValue();
            return;
        }
    }
    if (checkBigTemplateVerticalBounds(cell.getPosX(), cell.getPosY())) {
        Cell bot = getCell(cell.getPosX(), cell.getPosY() + 1);
        std::vector<Cell> hull = getBigVerticalHull(cell, bot);
        if (validateHull(hull) && validateKernel(cell, bot)) {
            cell.setCurValueOnField(1);
            cell.incMatchValue();
            return;
        }
    }
}

void Field::attachTemplateA2(Cell &cell) {
    if (checkBigTemplateHorizontalBounds(cell.getPosX() - 1, cell.getPosY())) {
        Cell left = getCell(cell.getPosX() - 1, cell.getPosY());
        std::vector<Cell> hull = getBigHorizontalHull(left, cell);
        if (validateHull(hull) && validateKernel(left, cell)) {
            cell.setCurValueOnField(1);
            cell.incMatchValue();
            return;
        }
    }
    if (checkBigTemplateVerticalBounds(cell.getPosX(), cell.getPosY() - 1)) {
        Cell top = getCell(cell.getPosX(), cell.getPosY() - 1);
        std::vector<Cell> hull = getBigVerticalHull(top, cell);
        if (validateHull(hull) && validateKernel(top, cell)) {
            cell.setCurValueOnField(1);
            cell.incMatchValue();
            return;
        }
    }
}

void Field::attachTemplateA3(Cell &cell) {
    if (checkBigTemplateHorizontalBounds(cell.getPosX(), cell.getPosY() + 1)) {
        Cell left = getCell(cell.getPosX(), cell.getPosY() + 1);
        Cell right = getCell(cell.getPosX() + 1, cell.getPosY() + 1);
        std::vector<Cell> hull = getBigHorizontalHull(left, right);
        if (validateHull(hull) && validateKernel(left, right)) {
            cell.setCurValueOnField(0);
            cell.incMatchValue();
            return;
        }
    }
    if (checkBigTemplateVerticalBounds(cell.getPosX() - 1, cell.getPosY())) {
        Cell top = getCell(cell.getPosX() - 1, cell.getPosY());
        Cell bot = getCell(cell.getPosX() - 1, cell.getPosY() + 1);
        std::vector<Cell> hull = getBigVerticalHull(top, bot);
        if (validateHull(hull) && validateKernel(top, bot)) {
            cell.setCurValueOnField(0);
            cell.incMatchValue();
            return;
        }
    }
}

void Field::attachTemplateA4(Cell &cell) {
    if (checkBigTemplateHorizontalBounds(cell.getPosX() - 1, cell.getPosY() + 1)) {
        Cell left = getCell(cell.getPosX() - 1, cell.getPosY() + 1);
        Cell right = getCell(cell.getPosX(), cell.getPosY() + 1);
        std::vector<Cell> hull = getBigHorizontalHull(left, right);
        if (validateHull(hull) && validateKernel(left, right)) {
            cell.setCurValueOnField(0);
            cell.incMatchValue();
            return;
        }
    }
    if (checkBigTemplateVerticalBounds(cell.getPosX() - 1, cell.getPosY() - 1)) {
        Cell top = getCell(cell.getPosX() - 1, cell.getPosY() - 1);
        Cell bot = getCell(cell.getPosX() - 1, cell.getPosY());
        std::vector<Cell> hull = getBigVerticalHull(top, bot);
        if (validateHull(hull) && validateKernel(top, bot)) {
            cell.setCurValueOnField(0);
            cell.incMatchValue();
            return;
        }
    }
}


void Field::attachTemplateA5(Cell &cell) {
    if (checkBigTemplateHorizontalBounds(cell.getPosX(), cell.getPosY() - 1)) {
        Cell left = getCell(cell.getPosX(), cell.getPosY() - 1);
        Cell right = getCell(cell.getPosX() + 1, cell.getPosY() - 1);
        std::vector<Cell> hull = getBigHorizontalHull(left, right);
        if (validateHull(hull) && validateKernel(left, right)) {
            cell.setCurValueOnField(0);
            cell.incMatchValue();
            return;
        }
    }
    if (checkBigTemplateVerticalBounds(cell.getPosX() + 1, cell.getPosY())) {
        Cell top = getCell(cell.getPosX() + 1, cell.getPosY());
        Cell bot = getCell(cell.getPosX() + 1, cell.getPosY() + 1);
        std::vector<Cell> hull = getBigVerticalHull(top, bot);
        if (validateHull(hull) && validateKernel(top, bot)) {
            cell.setCurValueOnField(0);
            cell.incMatchValue();
            return;
        }
    }
}

void Field::attachTemplateA6(Cell &cell) {
    if (checkBigTemplateHorizontalBounds(cell.getPosX() - 1, cell.getPosY() - 1)) {
        Cell left = getCell(cell.getPosX() - 1, cell.getPosY() - 1);
        Cell right = getCell(cell.getPosX(), cell.getPosY() - 1);
        std::vector<Cell> hull = getBigHorizontalHull(left, right);
        if (validateHull(hull) && validateKernel(left, right)) {
            cell.setCurValueOnField(0);
            cell.incMatchValue();
            return;
        }
    }
    if (checkBigTemplateVerticalBounds(cell.getPosX() + 1, cell.getPosY() - 1)) {
        Cell top = getCell(cell.getPosX() + 1, cell.getPosY() - 1);
        Cell bot = getCell(cell.getPosX() + 1, cell.getPosY());
        std::vector<Cell> hull = getBigVerticalHull(top, bot);
        if (validateHull(hull) && validateKernel(top, bot)) {
            cell.setCurValueOnField(0);
            cell.incMatchValue();
            return;
        }
    }
}


// A7 - A12 не используют все клетки для мэтчинга

void Field::attachTemplateA7(Cell &cell) {
    if (checkSmallTemplateBounds(cell.getPosX() + 1, cell.getPosY())) {
        Cell topLeftCorner = getCell(cell.getPosX(), cell.getPosY() - 1);
        Cell left = getCell(cell.getPosX() + 1, cell.getPosY());
        Cell right = getCell(cell.getPosX() + 2, cell.getPosY());
        std::vector<Cell> hull = getSmallHull(topLeftCorner, left, right);
        if (validateHull(hull) && validateKernel(left, right)) {
            cell.setCurValueOnField(0);
            cell.incMatchValue();
            return;
        }
    }
    if (checkSmallTemplateBounds(cell.getPosX(), cell.getPosY() + 1)) {
        Cell topLeftCorner = getCell(cell.getPosX() - 1, cell.getPosY());
        Cell top = getCell(cell.getPosX(), cell.getPosY() + 1);
        Cell bot = getCell(cell.getPosX(), cell.getPosY() + 2);
        std::vector<Cell> hull = getSmallHull(topLeftCorner, top,   bot);
        if (validateHull(hull) && validateKernel(top, bot)) {
            cell.setCurValueOnField(0);
            cell.incMatchValue();
            return;
        }
    }
}

void Field::attachTemplateA8(Cell &cell) {
    if (checkSmallTemplateBounds(cell.getPosX() - 1, cell.getPosY())) {
        Cell topLeftCorner = getCell(cell.getPosX() - 2, cell.getPosY() - 1);
        Cell left = getCell(cell.getPosX() - 2, cell.getPosY());
        Cell right = getCell(cell.getPosX() - 1, cell.getPosY());
        std::vector<Cell> hull = getSmallHull(topLeftCorner, left, right);
        if (validateHull(hull) && validateKernel(left, right)) {
            cell.setCurValueOnField(0);
            cell.incMatchValue();
            return;
        }

    }
    if (checkSmallTemplateBounds(cell.getPosX(), cell.getPosY() - 1)) {
        Cell topLeftCorner = getCell(cell.getPosX() - 1, cell.getPosY() - 2);
        Cell top = getCell(cell.getPosX(), cell.getPosY() - 2);
        Cell bot = getCell(cell.getPosX(), cell.getPosY() - 1);
        std::vector<Cell> hull = getSmallHull(topLeftCorner, top, bot);
        if (validateHull(hull) && validateKernel(top, bot)) {
            cell.setCurValueOnField(0);
            cell.incMatchValue();
            return;
        }
    }
}

void Field::attachTemplateA9(Cell &cell) {
    if (checkSmallTemplateBounds(cell.getPosX() + 1, cell.getPosY() + 1)) {
        Cell topLeftCorner = getCell(cell.getPosX(), cell.getPosY());
        Cell left = getCell(cell.getPosX() + 1, cell.getPosY() + 1);
        Cell right = getCell(cell.getPosX() + 2, cell.getPosY() + 1);
        std::vector<Cell> hull = getSmallHull(topLeftCorner, left, right);
        if (validateHull(hull) && validateKernel(left, right)) {
            cell.setCurValueOnField(0);
            cell.incMatchValue();
            return;
        }
    }
    if (checkSmallTemplateBounds(cell.getPosX() - 1, cell.getPosY() + 1)) {
        Cell topLeftCorner = getCell(cell.getPosX() - 2, cell.getPosY());
        Cell top = getCell(cell.getPosX() - 1, cell.getPosY() + 1);
        Cell bot = getCell(cell.getPosX() - 1, cell.getPosY() + 2);
        std::vector<Cell> hull = getSmallHull(topLeftCorner, top, bot);
        if (validateHull(hull) && validateKernel(top, bot)) {
            cell.setCurValueOnField(0);
            cell.incMatchValue();
            return;
        }
    }
}

void Field::attachTemplateA10(Cell &cell) {
    if (checkSmallTemplateBounds(cell.getPosX() - 1, cell.getPosY() + 1)) {
        Cell topLeftCorner = getCell(cell.getPosX() - 2, cell.getPosY());
        Cell left = getCell(cell.getPosX() - 2, cell.getPosY() + 1);
        Cell right = getCell(cell.getPosX() - 1, cell.getPosY() + 1);
        std::vector<Cell> hull = getSmallHull(topLeftCorner, left, right);
        if (validateHull(hull) && validateKernel(left, right)) {
            cell.setCurValueOnField(0);
            cell.incMatchValue();
            return;
        }
    }
    if (checkSmallTemplateBounds(cell.getPosX() - 1, cell.getPosY() - 1)) {
        Cell topLeftCorner = getCell(cell.getPosX() - 2, cell.getPosY() - 2);
        Cell top = getCell(cell.getPosX() - 1, cell.getPosY() - 2);
        Cell bot = getCell(cell.getPosX() - 1, cell.getPosY() - 1);
        std::vector<Cell> hull = getSmallHull(topLeftCorner, top, bot);
        if (validateHull(hull) && validateKernel(top, bot)) {
            cell.setCurValueOnField(0);
            cell.incMatchValue();
            return;
        }
    }
}

void Field::attachTemplateA11(Cell &cell) {
    if (checkSmallTemplateBounds(cell.getPosX() + 1, cell.getPosY() - 1)) {
        Cell topLeftCorner = getCell(cell.getPosX() - 2, cell.getPosY());
        Cell left = getCell(cell.getPosX() + 1, cell.getPosY() - 1);
        Cell right = getCell(cell.getPosX() + 2, cell.getPosY() - 1);
        std::vector<Cell> hull = getSmallHull(topLeftCorner, left, right);
        if (validateHull(hull) && validateKernel(left, right)) {
            cell.setCurValueOnField(0);
            cell.incMatchValue();
            return;
        }
    }
    if (checkSmallTemplateBounds(cell.getPosX() + 1, cell.getPosY() + 1)) {
        Cell topLeftCorner = getCell(cell.getPosX(), cell.getPosY());
        Cell top = getCell(cell.getPosX() + 1, cell.getPosY() + 1);
        Cell bot = getCell(cell.getPosX() + 1, cell.getPosY() + 2);
        std::vector<Cell> hull = getSmallHull(topLeftCorner, top, bot);
        if (validateHull(hull) && validateKernel(top, bot)) {
            cell.setCurValueOnField(0);
            cell.incMatchValue();
            return;
        }
    }
}

void Field::attachTemplateA12(Cell &cell) {
    if (checkSmallTemplateBounds(cell.getPosX() - 1, cell.getPosY() - 1)) {
        Cell topLeftCorner = getCell(cell.getPosX() - 2, cell.getPosY() - 2);
        Cell left = getCell(cell.getPosX() - 2, cell.getPosY() - 1);
        Cell right = getCell(cell.getPosX() - 1, cell.getPosY() - 1);
        std::vector<Cell> hull = getSmallHull(topLeftCorner, left, right);
        if (validateHull(hull) && validateKernel(left, right)) {
            cell.setCurValueOnField(0);
            cell.incMatchValue();
            return;
        }
    }
    if (checkSmallTemplateBounds(cell.getPosX() + 1, cell.getPosY() - 1)) {
        Cell topLeftCorner = getCell(cell.getPosX(), cell.getPosY() - 2);
        Cell top = getCell(cell.getPosX() + 1, cell.getPosY() - 2);
        Cell bot = getCell(cell.getPosX() + 1, cell.getPosY() - 1);
        std::vector<Cell> hull = getSmallHull(topLeftCorner, top, bot);
        if (validateHull(hull) && validateKernel(top, bot)) {
            cell.setCurValueOnField(0);
            cell.incMatchValue();
            return;
        }
    }
}

void Field::applyFirstRule(Cell &cell) {
    cell.setMatchValue(0);
    int oldValue = cell.getCurValueOnField();
    cell.setCurValueOnField(-1);
    attachTemplateA1(cell);
    if (cell.getMatchValue()) {
        return;
    }
    attachTemplateA2(cell);
    if (cell.getMatchValue()) {
        return;
    }
    attachTemplateA3(cell);
    if (cell.getMatchValue()) {
        return;
    }
    attachTemplateA4(cell);
    if (cell.getMatchValue()) {
        return;
    }
    attachTemplateA5(cell);
    if (cell.getMatchValue()) {
        return;
    }
    attachTemplateA6(cell);
    if (cell.getMatchValue()) {
        return;
    }
    attachTemplateA7(cell);
    if (cell.getMatchValue()) {
        return;
    }
    attachTemplateA8(cell);
    if (cell.getMatchValue()) {
        return;
    }
    attachTemplateA9(cell);
    if (cell.getMatchValue()) {
        return;
    }
    attachTemplateA10(cell);
    if (cell.getMatchValue()) {
        return;
    }
    attachTemplateA11(cell);
    if (cell.getMatchValue()) {
        return;
    }
    attachTemplateA12(cell);
    if (cell.getMatchValue()) {
        return;
    } else {
        bool TrueFalse = (rand() % 100) < PROBABILITY;
        if (TrueFalse) {
            cell.setCurValueOnField(rand() % 2);
        } else {
            cell.setCurValueOnField(oldValue);
        }
    }
}





