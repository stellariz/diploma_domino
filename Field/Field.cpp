//
// Created by ruslan on 05.11.2021.
//

#include <cmath>
#include "Field.h"


Field::Field() {
    bigPieceOfField = new Cell[(FieldConfig::WIDTH + 2) * (FieldConfig::LENGTH + 2)];
}


void Field::initField() {
    srand(time(NULL));
    for (int j = 0; j < FieldConfig::WIDTH + 2; ++j) {
        for (int i = 0; i < FieldConfig::LENGTH + 2; ++i) {
            if (j == 0 || i == 0 || j == FieldConfig::WIDTH + 1 || i == FieldConfig::LENGTH + 1) {
                bigPieceOfField[j * (FieldConfig::LENGTH + 2) + i].curValue = 0;
            } else {
                bigPieceOfField[j * (FieldConfig::LENGTH + 2) + i].curValue = rand() % 2;
            }
            bigPieceOfField[j * (FieldConfig::LENGTH + 2) + i].posX = i;
            bigPieceOfField[j * (FieldConfig::LENGTH + 2) + i].posY = j;
            bigPieceOfField[j * (FieldConfig::LENGTH + 2) + i].prevIterValue = bigPieceOfField[
                    j * (FieldConfig::LENGTH + 2) + i].curValue;
        }
    }
}


Field::~Field() {
    delete[] bigPieceOfField;
}


void Field::printMainField() {
    for (int j = 1; j < FieldConfig::WIDTH + 1; ++j) {
        for (int i = 1; i < FieldConfig::LENGTH + 1; ++i) {
            std::cout << "|";
            std::cout << bigPieceOfField[j * (FieldConfig::LENGTH + 2) + i].curValue;
        }
        std::cout << "|" << std::endl;
    }
    std::cout << std::endl;
}


bool Field::isInBounds(int x, int y) {
    return x >= 0 && x < FieldConfig::LENGTH + 2 &&
           y >= 0 && y < FieldConfig::WIDTH + 2;
}

bool Field::validateKernel(Cell &left, Cell &right) {
    return left.curValue != 0 && right.curValue != 0;
}

bool Field::validateHull(std::vector<Cell> &hull) {
    for (Cell &cell: hull) {
        if (cell.curValue == 1) {
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
    return isInBounds(x - 1, y + 2) &&
           isInBounds(x + 1, y + 2) &&
           isInBounds(x - 1, y - 1) &&
           isInBounds(x + 1, y - 1);
}


std::vector<Cell> Field::getSmallHull(Cell &leftTopCorner, Cell &firstKernelCell, Cell &secondKernelCell) {
    std::vector<Cell> area;
    for (int i = leftTopCorner.posY; i <= leftTopCorner.posY + 2; ++i) {
        for (int j = leftTopCorner.posX; j <= leftTopCorner.posX + 2; ++j) {
            if (bigPieceOfField[i * (FieldConfig::LENGTH + 2) + j] != firstKernelCell &&
                bigPieceOfField[i * (FieldConfig::LENGTH + 2) + j] != secondKernelCell) {
                area.push_back(bigPieceOfField[i * (FieldConfig::LENGTH + 2) + j]);
            }
        }
    }
    return area;
}

std::vector<Cell> Field::getBigVerticalHull(Cell &top, Cell &bottom) {
    std::vector<Cell> area;
    for (int i = top.posY - 1; i <= top.posY + 2; ++i) {
        for (int j = top.posX - 1; j <= top.posX + 1; ++j) {
            if (bigPieceOfField[i * (FieldConfig::LENGTH + 2) + j] != top &&
                bigPieceOfField[i * (FieldConfig::LENGTH + 2) + j] != bottom) {
                area.push_back(bigPieceOfField[i * (FieldConfig::LENGTH + 2) + j]);
            }
        }
    }
    return area;
}

std::vector<Cell> Field::getBigHorizontalHull(Cell &left, Cell &right) {
    std::vector<Cell> area;
    for (int i = left.posY - 1; i <= left.posY + 1; ++i) {
        for (int j = left.posX - 1; j <= left.posX + 2; ++j) {
            if (bigPieceOfField[i * (FieldConfig::LENGTH + 2) + j] != left &&
                bigPieceOfField[i * (FieldConfig::LENGTH + 2) + j] != right) {
                area.push_back(bigPieceOfField[i * (FieldConfig::LENGTH + 2) + j]);
            }
        }
    }
    return area;
}

void Field::attachTemplateA1(Cell &cell) {
    if (checkBigTemplateHorizontalBounds(cell.posX, cell.posY)) {
        Cell right = getCell(cell.posX + 1, cell.posY);
        std::vector<Cell> hull = getBigHorizontalHull(cell, right);
        if (validateHull(hull) && validateKernel(cell, right)) {
            cell.matchOneRefVal++;
        }
    }
    if (checkBigTemplateVerticalBounds(cell.posX, cell.posY)) {
        Cell bot = getCell(cell.posX, cell.posY + 1);
        std::vector<Cell> hull = getBigVerticalHull(cell, bot);
        if (validateHull(hull) && validateKernel(cell, bot)) {
            cell.matchOneRefVal++;
        }
    }
}

void Field::attachTemplateA2(Cell &cell) {
    if (checkBigTemplateHorizontalBounds(cell.posX - 1, cell.posY)) {
        Cell left = getCell(cell.posX - 1, cell.posY);
        std::vector<Cell> hull = getBigHorizontalHull(left, cell);
        if (validateHull(hull) && validateKernel(left, cell)) {
            cell.matchOneRefVal++;
        }
    }
    if (checkBigTemplateVerticalBounds(cell.posX, cell.posY - 1)) {
        Cell top = getCell(cell.posX, cell.posY - 1);
        std::vector<Cell> hull = getBigVerticalHull(top, cell);
        if (validateHull(hull) && validateKernel(top, cell)) {
            cell.matchOneRefVal++;
        }
    }
}

void Field::attachTemplateA3(Cell &cell) {
    if (checkBigTemplateHorizontalBounds(cell.posX, cell.posY + 1)) {
        Cell left = getCell(cell.posX, cell.posY + 1);
        Cell right = getCell(cell.posX + 1, cell.posY + 1);
        std::vector<Cell> hull = getBigHorizontalHull(left, right);
        if (validateHull(hull) && validateKernel(left, right)) {
            cell.matchZeroRefVal++;
        }
    }
    if (checkBigTemplateVerticalBounds(cell.posX - 1, cell.posY)) {
        Cell top = getCell(cell.posX - 1, cell.posY);
        Cell bot = getCell(cell.posX - 1, cell.posY + 1);
        std::vector<Cell> hull = getBigVerticalHull(top, bot);
        if (validateHull(hull) && validateKernel(top, bot)) {
            cell.matchZeroRefVal++;
        }
    }
}

void Field::attachTemplateA4(Cell &cell) {
    if (checkBigTemplateHorizontalBounds(cell.posX - 1, cell.posY + 1)) {
        Cell left = getCell(cell.posX - 1, cell.posY + 1);
        Cell right = getCell(cell.posX, cell.posY + 1);
        std::vector<Cell> hull = getBigHorizontalHull(left, right);
        if (validateHull(hull) && validateKernel(left, right)) {
            cell.matchZeroRefVal++;
        }
    }
    if (checkBigTemplateVerticalBounds(cell.posX - 1, cell.posY - 1)) {
        Cell top = getCell(cell.posX - 1, cell.posY - 1);
        Cell bot = getCell(cell.posX - 1, cell.posY);
        std::vector<Cell> hull = getBigVerticalHull(top, bot);
        if (validateHull(hull) && validateKernel(top, bot)) {
            cell.matchZeroRefVal++;
        }
    }
}


void Field::attachTemplateA5(Cell &cell) {
    if (checkBigTemplateHorizontalBounds(cell.posX, cell.posY - 1)) {
        Cell left = getCell(cell.posX, cell.posY - 1);
        Cell right = getCell(cell.posX + 1, cell.posY - 1);
        std::vector<Cell> hull = getBigHorizontalHull(left, right);
        if (validateHull(hull) && validateKernel(left, right)) {
            cell.matchZeroRefVal++;
        }
    }
    if (checkBigTemplateVerticalBounds(cell.posX + 1, cell.posY)) {
        Cell top = getCell(cell.posX + 1, cell.posY);
        Cell bot = getCell(cell.posX + 1, cell.posY + 1);
        std::vector<Cell> hull = getBigVerticalHull(top, bot);
        if (validateHull(hull) && validateKernel(top, bot)) {
            cell.matchZeroRefVal++;
        }
    }
}

void Field::attachTemplateA6(Cell &cell) {
    if (checkBigTemplateHorizontalBounds(cell.posX - 1, cell.posY - 1)) {
        Cell left = getCell(cell.posX - 1, cell.posY - 1);
        Cell right = getCell(cell.posX, cell.posY - 1);
        std::vector<Cell> hull = getBigHorizontalHull(left, right);
        if (validateHull(hull) && validateKernel(left, right)) {
            cell.matchZeroRefVal++;
        }
    }
    if (checkBigTemplateVerticalBounds(cell.posX + 1, cell.posY - 1)) {
        Cell top = getCell(cell.posX + 1, cell.posY - 1);
        Cell bot = getCell(cell.posX + 1, cell.posY);
        std::vector<Cell> hull = getBigVerticalHull(top, bot);
        if (validateHull(hull) && validateKernel(top, bot)) {
            cell.matchZeroRefVal++;
        }
    }
}


// A7 - A12 не используют все клетки для мэтчинга

void Field::attachTemplateA7(Cell &cell) {
    if (checkSmallTemplateBounds(cell.posX + 1, cell.posY)) {
        Cell topLeftCorner = getCell(cell.posX, cell.posY - 1);
        Cell left = getCell(cell.posX + 1, cell.posY);
        Cell right = getCell(cell.posX + 2, cell.posY);
        std::vector<Cell> hull = getSmallHull(topLeftCorner, left, right);
        if (validateHull(hull) && validateKernel(left, right)) {
            cell.matchZeroRefVal++;
        }
    }
    if (checkSmallTemplateBounds(cell.posX, cell.posY + 1)) {
        Cell topLeftCorner = getCell(cell.posX - 1, cell.posY);
        Cell top = getCell(cell.posX, cell.posY + 1);
        Cell bot = getCell(cell.posX, cell.posY + 2);
        std::vector<Cell> hull = getSmallHull(topLeftCorner, top, bot);
        if (validateHull(hull) && validateKernel(top, bot)) {
            cell.matchZeroRefVal++;
        }
    }
}

void Field::attachTemplateA8(Cell &cell) {
    if (checkSmallTemplateBounds(cell.posX - 1, cell.posY)) {
        Cell topLeftCorner = getCell(cell.posX - 2, cell.posY - 1);
        Cell left = getCell(cell.posX - 2, cell.posY);
        Cell right = getCell(cell.posX - 1, cell.posY);
        std::vector<Cell> hull = getSmallHull(topLeftCorner, left, right);
        if (validateHull(hull) && validateKernel(left, right)) {
            cell.matchZeroRefVal++;
        }

    }
    if (checkSmallTemplateBounds(cell.posX, cell.posY - 1)) {
        Cell topLeftCorner = getCell(cell.posX - 1, cell.posY - 2);
        Cell top = getCell(cell.posX, cell.posY - 2);
        Cell bot = getCell(cell.posX, cell.posY - 1);
        std::vector<Cell> hull = getSmallHull(topLeftCorner, top, bot);
        if (validateHull(hull) && validateKernel(top, bot)) {
            cell.matchZeroRefVal++;
        }
    }
}

void Field::attachTemplateA9(Cell &cell) {
    if (checkSmallTemplateBounds(cell.posX + 1, cell.posY + 1)) {
        Cell topLeftCorner = getCell(cell.posX, cell.posY);
        Cell left = getCell(cell.posX + 1, cell.posY + 1);
        Cell right = getCell(cell.posX + 2, cell.posY + 1);
        std::vector<Cell> hull = getSmallHull(topLeftCorner, left, right);
        if (validateHull(hull) && validateKernel(left, right)) {
            cell.matchZeroRefVal++;
        }
    }
    if (checkSmallTemplateBounds(cell.posX - 1, cell.posY + 1)) {
        Cell topLeftCorner = getCell(cell.posX - 2, cell.posY);
        Cell top = getCell(cell.posX - 1, cell.posY + 1);
        Cell bot = getCell(cell.posX - 1, cell.posY + 2);
        std::vector<Cell> hull = getSmallHull(topLeftCorner, top, bot);
        if (validateHull(hull) && validateKernel(top, bot)) {
            cell.matchZeroRefVal++;
        }
    }
}

void Field::attachTemplateA10(Cell &cell) {
    if (checkSmallTemplateBounds(cell.posX - 1, cell.posY + 1)) {
        Cell topLeftCorner = getCell(cell.posX - 2, cell.posY);
        Cell left = getCell(cell.posX - 2, cell.posY + 1);
        Cell right = getCell(cell.posX - 1, cell.posY + 1);
        std::vector<Cell> hull = getSmallHull(topLeftCorner, left, right);
        if (validateHull(hull) && validateKernel(left, right)) {
            cell.matchZeroRefVal++;
        }
    }
    if (checkSmallTemplateBounds(cell.posX - 1, cell.posY - 1)) {
        Cell topLeftCorner = getCell(cell.posX - 2, cell.posY - 2);
        Cell top = getCell(cell.posX - 1, cell.posY - 2);
        Cell bot = getCell(cell.posX - 1, cell.posY - 1);
        std::vector<Cell> hull = getSmallHull(topLeftCorner, top, bot);
        if (validateHull(hull) && validateKernel(top, bot)) {
            cell.matchZeroRefVal++;
        }
    }
}

void Field::attachTemplateA11(Cell &cell) {
    if (checkSmallTemplateBounds(cell.posX + 1, cell.posY - 1)) {
        Cell topLeftCorner = getCell(cell.posX, cell.posY - 2);
        Cell left = getCell(cell.posX + 1, cell.posY - 1);
        Cell right = getCell(cell.posX + 2, cell.posY - 1);
        std::vector<Cell> hull = getSmallHull(topLeftCorner, left, right);
        if (validateHull(hull) && validateKernel(left, right)) {
            cell.matchZeroRefVal++;
        }
    }
    if (checkSmallTemplateBounds(cell.posX + 1, cell.posY + 1)) {
        Cell topLeftCorner = getCell(cell.posX, cell.posY);
        Cell top = getCell(cell.posX + 1, cell.posY + 1);
        Cell bot = getCell(cell.posX + 1, cell.posY + 2);
        std::vector<Cell> hull = getSmallHull(topLeftCorner, top, bot);
        if (validateHull(hull) && validateKernel(top, bot)) {
            cell.matchZeroRefVal++;
        }
    }
}

void Field::attachTemplateA12(Cell &cell) {
    if (checkSmallTemplateBounds(cell.posX - 1, cell.posY - 1)) {
        Cell topLeftCorner = getCell(cell.posX - 2, cell.posY - 2);
        Cell left = getCell(cell.posX - 2, cell.posY - 1);
        Cell right = getCell(cell.posX - 1, cell.posY - 1);
        std::vector<Cell> hull = getSmallHull(topLeftCorner, left, right);
        if (validateHull(hull) && validateKernel(left, right)) {
            cell.matchZeroRefVal++;
        }
    }
    if (checkSmallTemplateBounds(cell.posX + 1, cell.posY - 1)) {
        Cell topLeftCorner = getCell(cell.posX, cell.posY - 2);
        Cell top = getCell(cell.posX + 1, cell.posY - 2);
        Cell bot = getCell(cell.posX + 1, cell.posY - 1);
        std::vector<Cell> hull = getSmallHull(topLeftCorner, top, bot);
        if (validateHull(hull) && validateKernel(top, bot)) {
            cell.matchZeroRefVal++;
        }
    }
}

void Field::applyTemplates(Cell &cell) {
    cell.matchZeroRefVal = 0;
    cell.matchOneRefVal = 0;
    cell.hitValue = -1;
    int oldValue = cell.curValue;
    cell.curValue = -1;
    attachTemplateA1(cell);
    attachTemplateA2(cell);
    attachTemplateA3(cell);
    attachTemplateA4(cell);
    attachTemplateA5(cell);
    attachTemplateA6(cell);
    attachTemplateA7(cell);
    attachTemplateA8(cell);
    attachTemplateA9(cell);
    attachTemplateA10(cell);
    attachTemplateA11(cell);
    attachTemplateA12(cell);
    cell.countHitValue();
    cell.curValue = oldValue;
    applyARule(cell);
}

void Field::applyARule(Cell &cell) {
    if (cell.hitValue > 0 && cell.hitValue != 100) {
        cell.curValue = 0;
    } else if (cell.hitValue == 100) {
        cell.curValue = 1;
    } else if (cell.hitValue == 0) {
        bool trueFalse = (rand() % 100) < PROBABILITY00;
        if (trueFalse) {
            cell.curValue = rand() % 2;
        }
    }
}


int Field::validateField() {
    int numBlackCell = 0;
    for (int j = 1; j < FieldConfig::WIDTH + 1; ++j) {
        for (int i = 1; i < FieldConfig::LENGTH + 1; ++i) {
            Cell &cell = bigPieceOfField[j * (FieldConfig::LENGTH + 2) + i];
            cell.matchZeroRefVal = 0;
            cell.matchOneRefVal = 0;
            int oldValue = cell.curValue;
            cell.curValue = -1;
            attachTemplateA1(cell);
            attachTemplateA2(cell);
            attachTemplateA3(cell);
            attachTemplateA4(cell);
            attachTemplateA5(cell);
            attachTemplateA6(cell);
            attachTemplateA7(cell);
            attachTemplateA8(cell);
            attachTemplateA9(cell);
            attachTemplateA10(cell);
            attachTemplateA11(cell);
            attachTemplateA12(cell);
            cell.curValue = oldValue;
            if (cell.curValue == 1 && cell.matchOneRefVal != 0) {
                numBlackCell++;
            } else if (cell.matchOneRefVal == 0 || cell.matchZeroRefVal == 0){
                return -1;
            }
        }
    }
    return numBlackCell / 2;
}

int Field::updateEvolveState() {
    int changedCell = 0;
    for (int j = 1; j < FieldConfig::WIDTH + 1; ++j) {
        for (int i = 1; i < FieldConfig::LENGTH + 1; ++i) {
            auto &cell = getCell(i, j);
            if (cell.curValue != cell.prevIterValue) {
                changedCell++;
            }
            cell.prevIterValue = cell.curValue;
        }
    }
    return changedCell;
}





