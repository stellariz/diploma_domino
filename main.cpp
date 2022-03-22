#include "Field/Field.h"
#include "Field/FieldConfig.h"

void updateField(Field &field) {
    int randomX = rand() % FieldConfig::LENGTH + 1;
    int randomY = rand() % FieldConfig::WIDTH + 1;
    field.applyTemplates(field.getCell(randomX, randomY));
}


int main() {
    int dominoes[] = {0, 0, 0, 0, 0, 0};
    for (int k = 0; k < 1000; ++k) {
        Field field;
        for (int i = 0; i < 200; ++i) {
            for (int j = 0; j < FieldConfig::LENGTH * FieldConfig::WIDTH; ++j) {
                updateField(field);
            }
            int numOfDominoes = field.validateField();
            if (numOfDominoes) {
                dominoes[numOfDominoes-5]++;
                break;
            }
        }
    }
    for (int domino : dominoes) {
        std::cout << domino << " ";
    }
    return 0;
}
