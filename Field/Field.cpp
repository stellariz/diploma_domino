//
// Created by ruslan on 05.11.2021.
//

#include "Field.h"

Field::Field(int sizeOfPiece, int rank, int size) {
    srand(time(NULL) + rank);
    if (rank == 0) {
        bigPieceOfField = new Cell[sizeOfPiece + 3 * FieldConfig::LENGTH];
        for (int j = 0; j < sizeOfPiece / FieldConfig::LENGTH; ++j) {
            for (int i = 0; i < FieldConfig::LENGTH; ++i) {
                bigPieceOfField[j * FieldConfig::LENGTH + i].curValue = rand() % 2;
                bigPieceOfField[j * FieldConfig::LENGTH + i].posX = i;
                bigPieceOfField[j * FieldConfig::LENGTH + i].posY = j;
            }
        }
    } else if (rank == size - 1) {
        bigPieceOfField = new Cell[sizeOfPiece + 3 * FieldConfig::LENGTH];
        for (int j = 3; j < sizeOfPiece / FieldConfig::LENGTH + 3; ++j) {
            for (int i = 0; i < FieldConfig::LENGTH; ++i) {
                bigPieceOfField[j * FieldConfig::LENGTH + i].curValue = rand() % 2;
                bigPieceOfField[j * FieldConfig::LENGTH + i].posX = i;
                bigPieceOfField[j * FieldConfig::LENGTH + i].posY = j;
            }
        }
    } else {
        bigPieceOfField = new Cell[sizeOfPiece + 6 * FieldConfig::LENGTH];
        for (int j = 3; j < sizeOfPiece / FieldConfig::LENGTH + 3; ++j) {
            for (int i = 0; i < FieldConfig::LENGTH; ++i) {
                bigPieceOfField[j * FieldConfig::LENGTH + i].curValue = rand() % 2;
                bigPieceOfField[j * FieldConfig::LENGTH + i].posX = i;
                bigPieceOfField[j * FieldConfig::LENGTH + i].posY = j;
            }
        }
    }
}


Field::~Field() {
    delete[] bigPieceOfField;
}


void Field::printMainField(int rank, int size, int sizeOfPiece) {
    if (rank == 0) {
        for (int j = 0; j < sizeOfPiece / FieldConfig::LENGTH; ++j) {
            for (int i = 0; i < FieldConfig::LENGTH; ++i) {
                std::cout << "|";
                std::cout << bigPieceOfField[j * FieldConfig::LENGTH + i].curValue;
            }
            std::cout << "|" << std::endl;
        }
    } else {
        for (int j = 3; j < sizeOfPiece / FieldConfig::LENGTH + 3; ++j) {
            for (int i = 0; i < FieldConfig::LENGTH; ++i) {
                std::cout << "|";
                std::cout << bigPieceOfField[j * FieldConfig::LENGTH + i].curValue;
            }
            std::cout << "|" << std::endl;
        }
    }
    if (rank == size - 1){
        std::cout << std::endl;
    }
}


bool Field::isInBounds(int x, int y) {
    return x >= 0 && x < FieldConfig::LENGTH &&
           y >= 0 && y < FieldConfig::WIDTH;
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
    return isInBounds(x - 1, y + 1) &&
           isInBounds(x + 1, y + 1) &&
           isInBounds(x - 1, y - 2) &&
           isInBounds(x + 1, y - 2);
}


std::vector<Cell> Field::getSmallHull(Cell &leftTopCorner, Cell &firstKernelCell, Cell &secondKernelCell) {
    std::vector<Cell> area;
    for (int i = leftTopCorner.posY; i <= leftTopCorner.posY + 2; ++i) {
        for (int j = leftTopCorner.posX; j <= leftTopCorner.posX + 2; ++j) {
            if (bigPieceOfField[i * FieldConfig::LENGTH + j] != firstKernelCell &&
                bigPieceOfField[i * FieldConfig::LENGTH + j] != secondKernelCell) {
                area.push_back(bigPieceOfField[i * FieldConfig::LENGTH + j]);
            }
        }
    }
    return area;
}

std::vector<Cell> Field::getBigVerticalHull(Cell &top, Cell &bottom) {
    std::vector<Cell> area;
    for (int i = top.posY - 1; i <= top.posY + 2; ++i) {
        for (int j = top.posX - 1; j <= top.posX + 1; ++j) {
            if (bigPieceOfField[i * FieldConfig::LENGTH + j] != top &&
                bigPieceOfField[i * FieldConfig::LENGTH + j] != bottom) {
                area.push_back(bigPieceOfField[i * FieldConfig::LENGTH + j]);
            }
        }
    }
    return area;
}

std::vector<Cell> Field::getBigHorizontalHull(Cell &left, Cell &right) {
    std::vector<Cell> area;
    for (int i = left.posY - 1; i <= left.posY + 1; ++i) {
        for (int j = left.posX - 1; j <= left.posX + 2; ++j) {
            if (bigPieceOfField[i * FieldConfig::LENGTH + j] != left &&
                bigPieceOfField[i * FieldConfig::LENGTH + j] != right) {
                area.push_back(bigPieceOfField[i * FieldConfig::LENGTH + j]);
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
            cell.curValue = 1;
            cell.matchValue++;
            return;
        }
    }
    if (checkBigTemplateVerticalBounds(cell.posX, cell.posY)) {
        Cell bot = getCell(cell.posX, cell.posY + 1);
        std::vector<Cell> hull = getBigVerticalHull(cell, bot);
        if (validateHull(hull) && validateKernel(cell, bot)) {
            cell.curValue = 1;
            cell.matchValue++;
            return;
        }
    }
}

void Field::attachTemplateA2(Cell &cell) {
    if (checkBigTemplateHorizontalBounds(cell.posX - 1, cell.posY)) {
        Cell left = getCell(cell.posX - 1, cell.posY);
        std::vector<Cell> hull = getBigHorizontalHull(left, cell);
        if (validateHull(hull) && validateKernel(left, cell)) {
            cell.curValue = 1;
            cell.matchValue++;
            return;
        }
    }
    if (checkBigTemplateVerticalBounds(cell.posX, cell.posY - 1)) {
        Cell top = getCell(cell.posX, cell.posY - 1);
        std::vector<Cell> hull = getBigVerticalHull(top, cell);
        if (validateHull(hull) && validateKernel(top, cell)) {
            cell.curValue = 1;
            cell.matchValue++;
            return;
        }
    }
}

void Field::attachTemplateA3(Cell &cell) {
    if (checkBigTemplateHorizontalBounds(cell.posX, cell.posY + 1)) {
        Cell left = getCell(cell.posX, cell.posY + 1);
        Cell right = getCell(cell.posX + 1, cell.posY + 1);
        std::vector<Cell> hull = getBigHorizontalHull(left, right);
        if (validateHull(hull) && validateKernel(left, right)) {
            cell.curValue = 0;
            cell.matchValue++;
            return;
        }
    }
    if (checkBigTemplateVerticalBounds(cell.posX - 1, cell.posY)) {
        Cell top = getCell(cell.posX - 1, cell.posY);
        Cell bot = getCell(cell.posX - 1, cell.posY + 1);
        std::vector<Cell> hull = getBigVerticalHull(top, bot);
        if (validateHull(hull) && validateKernel(top, bot)) {
            cell.curValue = 0;
            cell.matchValue++;
            return;
        }
    }
}

void Field::attachTemplateA4(Cell &cell) {
    if (checkBigTemplateHorizontalBounds(cell.posX - 1, cell.posY + 1)) {
        Cell left = getCell(cell.posX - 1, cell.posY + 1);
        Cell right = getCell(cell.posX, cell.posY + 1);
        std::vector<Cell> hull = getBigHorizontalHull(left, right);
        if (validateHull(hull) && validateKernel(left, right)) {
            cell.curValue = 0;
            cell.matchValue++;
            return;
        }
    }
    if (checkBigTemplateVerticalBounds(cell.posX - 1, cell.posY - 1)) {
        Cell top = getCell(cell.posX - 1, cell.posY - 1);
        Cell bot = getCell(cell.posX - 1, cell.posY);
        std::vector<Cell> hull = getBigVerticalHull(top, bot);
        if (validateHull(hull) && validateKernel(top, bot)) {
            cell.curValue = 0;
            cell.matchValue++;
            return;
        }
    }
}


void Field::attachTemplateA5(Cell &cell) {
    if (checkBigTemplateHorizontalBounds(cell.posX, cell.posY - 1)) {
        Cell left = getCell(cell.posX, cell.posY - 1);
        Cell right = getCell(cell.posX + 1, cell.posY - 1);
        std::vector<Cell> hull = getBigHorizontalHull(left, right);
        if (validateHull(hull) && validateKernel(left, right)) {
            cell.curValue = 0;
            cell.matchValue++;
            return;
        }
    }
    if (checkBigTemplateVerticalBounds(cell.posX + 1, cell.posY)) {
        Cell top = getCell(cell.posX + 1, cell.posY);
        Cell bot = getCell(cell.posX + 1, cell.posY + 1);
        std::vector<Cell> hull = getBigVerticalHull(top, bot);
        if (validateHull(hull) && validateKernel(top, bot)) {
            cell.curValue = 0;
            cell.matchValue++;
            return;
        }
    }
}

void Field::attachTemplateA6(Cell &cell) {
    if (checkBigTemplateHorizontalBounds(cell.posX - 1, cell.posY - 1)) {
        Cell left = getCell(cell.posX - 1, cell.posY - 1);
        Cell right = getCell(cell.posX, cell.posY - 1);
        std::vector<Cell> hull = getBigHorizontalHull(left, right);
        if (validateHull(hull) && validateKernel(left, right)) {
            cell.curValue = 0;
            cell.matchValue++;
            return;
        }
    }
    if (checkBigTemplateVerticalBounds(cell.posX + 1, cell.posY - 1)) {
        Cell top = getCell(cell.posX + 1, cell.posY - 1);
        Cell bot = getCell(cell.posX + 1, cell.posY);
        std::vector<Cell> hull = getBigVerticalHull(top, bot);
        if (validateHull(hull) && validateKernel(top, bot)) {
            cell.curValue = 0;
            cell.matchValue++;
            return;
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
            cell.curValue = 0;
            cell.matchValue++;
            return;
        }
    }
    if (checkSmallTemplateBounds(cell.posX, cell.posY + 1)) {
        Cell topLeftCorner = getCell(cell.posX - 1, cell.posY);
        Cell top = getCell(cell.posX, cell.posY + 1);
        Cell bot = getCell(cell.posX, cell.posY + 2);
        std::vector<Cell> hull = getSmallHull(topLeftCorner, top, bot);
        if (validateHull(hull) && validateKernel(top, bot)) {
            cell.curValue = 0;
            cell.matchValue++;
            return;
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
            cell.curValue = 0;
            cell.matchValue++;
            return;
        }

    }
    if (checkSmallTemplateBounds(cell.posX, cell.posY - 1)) {
        Cell topLeftCorner = getCell(cell.posX - 1, cell.posY - 2);
        Cell top = getCell(cell.posX, cell.posY - 2);
        Cell bot = getCell(cell.posX, cell.posY - 1);
        std::vector<Cell> hull = getSmallHull(topLeftCorner, top, bot);
        if (validateHull(hull) && validateKernel(top, bot)) {
            cell.curValue = 0;
            cell.matchValue++;
            return;
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
            cell.curValue = 0;
            cell.matchValue++;
            return;
        }
    }
    if (checkSmallTemplateBounds(cell.posX - 1, cell.posY + 1)) {
        Cell topLeftCorner = getCell(cell.posX - 2, cell.posY);
        Cell top = getCell(cell.posX - 1, cell.posY + 1);
        Cell bot = getCell(cell.posX - 1, cell.posY + 2);
        std::vector<Cell> hull = getSmallHull(topLeftCorner, top, bot);
        if (validateHull(hull) && validateKernel(top, bot)) {
            cell.curValue = 0;
            cell.matchValue++;
            return;
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
            cell.curValue = 0;
            cell.matchValue++;
            return;
        }
    }
    if (checkSmallTemplateBounds(cell.posX - 1, cell.posY - 1)) {
        Cell topLeftCorner = getCell(cell.posX - 2, cell.posY - 2);
        Cell top = getCell(cell.posX - 1, cell.posY - 2);
        Cell bot = getCell(cell.posX - 1, cell.posY - 1);
        std::vector<Cell> hull = getSmallHull(topLeftCorner, top, bot);
        if (validateHull(hull) && validateKernel(top, bot)) {
            cell.curValue = 0;
            cell.matchValue++;
            return;
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
            cell.curValue = 0;
            cell.matchValue++;
            return;
        }
    }
    if (checkSmallTemplateBounds(cell.posX + 1, cell.posY + 1)) {
        Cell topLeftCorner = getCell(cell.posX, cell.posY);
        Cell top = getCell(cell.posX + 1, cell.posY + 1);
        Cell bot = getCell(cell.posX + 1, cell.posY + 2);
        std::vector<Cell> hull = getSmallHull(topLeftCorner, top, bot);
        if (validateHull(hull) && validateKernel(top, bot)) {
            cell.curValue = 0;
            cell.matchValue++;
            return;
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
            cell.curValue = 0;
            cell.matchValue++;
            return;
        }
    }
    if (checkSmallTemplateBounds(cell.posX + 1, cell.posY - 1)) {
        Cell topLeftCorner = getCell(cell.posX, cell.posY - 2);
        Cell top = getCell(cell.posX + 1, cell.posY - 2);
        Cell bot = getCell(cell.posX + 1, cell.posY - 1);
        std::vector<Cell> hull = getSmallHull(topLeftCorner, top, bot);
        if (validateHull(hull) && validateKernel(top, bot)) {
            cell.curValue = 0;
            cell.matchValue++;
            return;
        }
    }
}

void Field::applyFirstRule(Cell &cell, int shift) {
    cell.matchValue = 0;
    int oldValue = cell.curValue;
    cell.curValue = -1;
    attachTemplateA1(cell);
    if (cell.matchValue) {
        return;
    }
    attachTemplateA2(cell);
    if (cell.matchValue) {
        return;
    }
    attachTemplateA3(cell);
    if (cell.matchValue) {
        return;
    }
    attachTemplateA4(cell);
    if (cell.matchValue) {
        return;
    }
    attachTemplateA5(cell);
    if (cell.matchValue) {
        return;
    }
    attachTemplateA6(cell);
    if (cell.matchValue) {
        return;
    }
    attachTemplateA7(cell);
    if (cell.matchValue) {
        return;
    }
    attachTemplateA8(cell);
    if (cell.matchValue) {
        return;
    }
    attachTemplateA9(cell);
    if (cell.matchValue) {
        return;
    }
    attachTemplateA10(cell);
    if (cell.matchValue) {
        return;
    }
    attachTemplateA11(cell);
    if (cell.matchValue) {
        return;
    }
    attachTemplateA12(cell);
    if (cell.matchValue) {
        return;
    } else {
        bool TrueFalse = (rand() % 100) < PROBABILITY;
        if (TrueFalse) {
            cell.curValue = rand() % 2;
        } else {
            cell.curValue = oldValue;
        }
    }
}


Cell *Field::getMainField() {
    return bigPieceOfField;
}

Cell *Field::getUpperBound(int rank, int size) {
    if (rank == 0) {
        return bigPieceOfField + size;
    }
    return bigPieceOfField + size + 3 * FieldConfig::LENGTH;
}

Cell *Field::getLowerBound(int rank) {
    if (rank == 0) {
        return bigPieceOfField;
    }
    return bigPieceOfField + 3 * FieldConfig::LENGTH;
}






