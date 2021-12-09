#include "Field/Field.h"
#include <mpi/mpi.h>
#include <unistd.h>

void updateField(Field &field) {
    int randomX = rand() % FieldConfig::LENGTH;
    int randomY = rand() % FieldConfig::WIDTH;
    Cell chosenCell = field.getCell(randomX, randomY);
    field.applyFirstRule(chosenCell);
}

int main(int argc, char **argv) {
    Field field;
    field.printField();
    for (int i = 0; i < 10000; ++i) {
        for (int j = 0; j < FieldConfig::LENGTH * FieldConfig::WIDTH; ++j) {
            updateField(field);
        }
    }
    field.printField();
    return 0;
}
