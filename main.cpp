#include "Field/Field.h"
#include "Field/FieldConfig.h"

void updateField(Field &field) {
    int randomX = rand() % FieldConfig::LENGTH;
    int randomY = rand() % FieldConfig::WIDTH;
    field.applyFirstRule(field.getCell(randomX, randomY));
}

int main(int argc, char **argv) {
    Field field;
    field.printField();
    for (int i = 0; i < 5000; ++i) {
        for (int j = 0; j < FieldConfig::LENGTH * FieldConfig::WIDTH; ++j) {
            updateField(field);
        }
        field.printField();
    }
    return 0;
}
