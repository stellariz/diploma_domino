#include "Field/Field.h"
#include "Field/FieldConfig.h"

void updateField(Field &field) {
    int randomX = rand() % FieldConfig::LENGTH + 1;
    int randomY = rand() % FieldConfig::WIDTH + 1;
    field.applyTemplates(field.getCell(randomX, randomY));
}


int main() {
    int dominoes[] = {0, 0, 0, 0, 0, 0};
    int nonGapState = 2;
    double t_avg = 0;
    Field field;
    for (int k = 0; k < 1000; ++k) {
        field.initField();
        for (int i = 0; i < 200; ++i) {
            for (int j = 0; j < FieldConfig::LENGTH * FieldConfig::WIDTH*2; ++j) {
                updateField(field);
            }
            int changedCells = field.updateEvolveState();
            int numOfDominoes = field.validateField();
            if (changedCells <= nonGapState && numOfDominoes >= 5) {
                dominoes[numOfDominoes - 5]++;
                t_avg += i;
                break;
            }
        }
    }
    for (int domino: dominoes) {
        std::cout << domino << " ";
    }
    std::cout << std::endl;
    std::cout << "t_avg= " << t_avg / 1000;
    return 0;
}
